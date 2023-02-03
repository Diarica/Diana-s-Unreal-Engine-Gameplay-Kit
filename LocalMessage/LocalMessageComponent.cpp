// Fill out your copyright notice in the Description page of Project Settings.


#include "LocalMessageComponent.h"

#include "GameplayTagContainer.h"
#include "Kismet/KismetSystemLibrary.h"




ULocalMessageComponent::ULocalMessageComponent()
{
	PrimaryComponentTick.SetTickFunctionEnable(false);
	PrimaryComponentTick.bCanEverTick = false;
}

void ULocalMessageComponent::BroadcastMessageInternal(FGameplayTag Channel, const UScriptStruct* StructType,
	const void* MessageBytes)
{
	bool bOnInitialTag = true;
	for (FGameplayTag Tag = Channel; Tag.IsValid(); Tag = Tag.RequestDirectParent())
	{
		if (const FChannelListenerList* pList = ListenerMap.Find(Tag))
		{
			// Copy in case there are removals while handling callbacks
			TArray<FLocalMessageListenerData> ListenerArray(pList->Listeners);

			for (const FLocalMessageListenerData& Listener : ListenerArray)
			{
				if (bOnInitialTag || (Listener.MatchType == ELocalMessageMatchType::EMMT_Partical))
				{
					if (Listener.bHadValidType && !Listener.ListenerStructType.IsValid())
					{
						
						UnregisterListenerInternal(Channel, Listener.HandleID);
						continue;
					}

					// The receiving type must be either a parent of the sending type or completely ambiguous (for internal use)
					if (!Listener.bHadValidType || StructType->IsChildOf(Listener.ListenerStructType.Get()))
					{
						Listener.MessageCallback(Channel, StructType, MessageBytes);
					}
					else
					{
						
					}
				}
			}
		}
		bOnInitialTag = false;
	}
	
}

FLocalMessageListenerHandle ULocalMessageComponent::RegisterListenerInternal(FGameplayTag Channel,
                                                                             TFunction<void(FGameplayTag, const UScriptStruct*, const void*)>&& Callback, const UScriptStruct* StructType,
                                                                             ELocalMessageMatchType MatchType)
{
	if(!Channel.IsValid())
	{
		return FLocalMessageListenerHandle();
	}
	FChannelListenerList& List = ListenerMap.FindOrAdd(Channel);

	FLocalMessageListenerData& Entry = List.Listeners.AddDefaulted_GetRef();
	Entry.MessageCallback = MoveTemp(Callback);
	Entry.ListenerStructType = StructType;
	Entry.bHadValidType = StructType != nullptr;
	Entry.HandleID = ++List.HandleID;
	Entry.MatchType = MatchType;

	return FLocalMessageListenerHandle(Channel,Entry.HandleID);
}

void ULocalMessageComponent::UnregisterListener(FLocalMessageListenerHandle Handle)
{
	if(Handle.IsValid())
	{
		UnregisterListenerInternal(Handle.Channel,Handle.ID);
	}
}

void ULocalMessageComponent::UnregisterListenerInternal(FGameplayTag Channel, int32 HandleID)
{
	if(FChannelListenerList* ptrList = ListenerMap.Find(Channel))
	{
		int32 MatchIndex = ptrList->Listeners.IndexOfByPredicate([ID = HandleID](const FLocalMessageListenerData& Other){return Other.HandleID == ID;});
		if(MatchIndex != INDEX_NONE)
		{
			ptrList->Listeners.RemoveAtSwap(MatchIndex);
		}

		if(ptrList->Listeners.Num() == 0)
		{
			ListenerMap.Remove(Channel);
		}
	}
}

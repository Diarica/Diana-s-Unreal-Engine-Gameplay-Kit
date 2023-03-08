// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "LocalMessageTypes.h"
#include "Components/ActorComponent.h"
#include "GameplayMessageProcessor.generated.h"





//Gameplay Message Component,Scope on Actor
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UGameplayMessageProcessor : public UActorComponent
{
	GENERATED_BODY()

public:
	


	

public:
	// Sets default values for this component's properties
	UGameplayMessageProcessor();





	template <typename FMessageStructType>
	void BroadcastMessage(FGameplayTag Channel,const FMessageStructType& Message)
	{
		const UScriptStruct* StructType = TBaseStructure<FMessageStructType>::Get();
		BroadcastMessageInternal(Channel, StructType, &Message);
	}

	



	template <typename FMessageStructType>
	FLocalMessageListenerHandle RegisterListener(FGameplayTag Channel,FLocalMessageListenerParams<FMessageStructType>& Params )
	{
		
		FLocalMessageListenerHandle Handle;

		if(Params.OnMessageReceivedCallback)
		{
			auto ThunkCallback = [InnerCallback = Params.OnMessageReceivedCallback](FGameplayTag ActualTag,const UScriptStruct* SenderStructType,const void* SenderPayload)
			{
				InnerCallback(ActualTag,*reinterpret_cast<const FMessageStructType*>(SenderPayload));
			};

			const UScriptStruct* StructType = TBaseStructure<FMessageStructType>::Get();
			Handle = RegisterListenerInternal(Channel,ThunkCallback,StructType,Params.MatchType);
			
		}
		return Handle;
	}
	

	
	template <typename FMessageStructType, typename TOwner = UObject>
	FLocalMessageListenerHandle RegisterListener(FGameplayTag Channel, TOwner* Object, void(TOwner::* Function)(FGameplayTag, const FMessageStructType&))
	{
		TWeakObjectPtr<TOwner> WeakObject(Object);

		return RegisterListener<FMessageStructType>(Channel,[WeakObject,Function](FGameplayTag Channel,const FMessageStructType& Payload)
		{
			if(TOwner* StrongObject = WeakObject.Get())
			{
				(StrongObject->*Function(Channel,Payload));
			}
			
		});
	}
	
	template <typename FMessageStructType>
	FLocalMessageListenerHandle RegisterListener(FGameplayTag Channel, TFunction<void(FGameplayTag, const FMessageStructType&)>&& Callback, ELocalMessageMatchType MatchType = ELocalMessageMatchType::EMMT_Exact)
	{
		auto ThunkCallback = [InnerCallback = MoveTemp(Callback)](FGameplayTag ActualTag, const UScriptStruct* SenderStructType, const void* SenderPayload)
		{
			InnerCallback(ActualTag, *reinterpret_cast<const FMessageStructType*>(SenderPayload));
		};

		const UScriptStruct* StructType = TBaseStructure<FMessageStructType>::Get();
		return RegisterListenerInternal(Channel, ThunkCallback, StructType, MatchType);
	}
	


	void UnregisterListener(FLocalMessageListenerHandle Handle);





private:
	struct FChannelListenerList
	{
		TArray<FLocalMessageListenerData> Listeners;
		int32 HandleID = 0;
	};

	
	TMap<FGameplayTag,FChannelListenerList> ListenerMap;

	FLocalMessageListenerHandle RegisterListenerInternal(
		FGameplayTag Channel, 
		TFunction<void(FGameplayTag, const UScriptStruct*, const void*)>&& Callback,
		const UScriptStruct* StructType,
		ELocalMessageMatchType MatchType);

	void UnregisterListenerInternal(FGameplayTag Channel,int32 HandleID);
	
	

	
	void BroadcastMessageInternal(FGameplayTag Channel,const UScriptStruct* StructType,const void* MessageBytes);
	
};

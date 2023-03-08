#pragma once
#include "GameplayMessageProcessor.h"
UENUM()
enum ELocalMessageMatchType
{
	EMMT_Partical,
	EMMT_Exact,
	
};



template<typename FMessageStructType>
	struct FLocalMessageListenerParams
{
	ELocalMessageMatchType MatchType = ELocalMessageMatchType::EMMT_Exact;

	TFunction<void(FGameplayTag, const FMessageStructType&)> OnMessageReceivedCallback;

	template<typename TOwner = UObject>
void SetMessageReceivedCallback(TOwner* Object, void(TOwner::* Function)(FGameplayTag, const FMessageStructType&))
	{
		TWeakObjectPtr<TOwner> WeakObject(Object);
		OnMessageReceivedCallback = [WeakObject, Function](FGameplayTag Channel, const FMessageStructType& Payload)
		{
			if (TOwner* StrongObject = WeakObject.Get())
			{
				(StrongObject->*Function)(Channel, Payload);
			}
		};
	}
		
};


USTRUCT()
struct FLocalMessageListenerHandle
{
	GENERATED_BODY()

	FLocalMessageListenerHandle(){}
	FLocalMessageListenerHandle(FGameplayTag InChannel,int32 InID) : ID(InID),Channel(InChannel){};
	
	
	
	UPROPERTY(Transient)
	int32 ID = 0;

	bool IsValid() const{return ID != 0;}

	void Unregister();

	UPROPERTY(Transient)
	FGameplayTag Channel;

	
	
	
};

USTRUCT()
struct FLocalMessageListenerData
{
	GENERATED_BODY()

	TFunction<void(FGameplayTag,const UScriptStruct*,const void*)> MessageCallback;

	int32 HandleID;

	ELocalMessageMatchType MatchType;

	TWeakObjectPtr<const UScriptStruct> ListenerStructType = nullptr;

	bool bHadValidType = false;
	
	
};


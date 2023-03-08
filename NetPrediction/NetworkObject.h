// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/NetDriver.h"
#include "UObject/Object.h"
#include "NetworkObject.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class UNetworkObject : public UObject
{
	GENERATED_BODY()
public:
	

public:
	virtual bool IsSupportedForNetworking() const override
	{
		return true;
	}

	virtual int32 GetFunctionCallspace(UFunction* Function, FFrame* Stack)
	{
		int32 Callspace = FunctionCallspace::Local;
		if (UObject* Outer = GetOuter()) Callspace = Outer->GetFunctionCallspace(Function, Stack);
		return Callspace;
	}

	

	UPROPERTY()
	int UnUsed;

	AActor* GetActorOuter() const
	{
		return GetTypedOuter<AActor>();
	}

	virtual bool CallRemoteFunction(UFunction* Function, void* Parms, FOutParmRec* OutParms, FFrame* Stack) override
	{
		AActor* Actor = GetTypedOuter<AActor>();
		if (UNetDriver* NetDriver = Actor->GetNetDriver())
		{
			NetDriver->ProcessRemoteFunction(Actor, Function, Parms, OutParms, Stack, this);
			return true;
		}
		return false;
	}
	
};
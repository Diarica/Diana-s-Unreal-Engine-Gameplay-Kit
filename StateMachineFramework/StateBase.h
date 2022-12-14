// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "StateBase.generated.h"

/**
 * 
 */
UCLASS()
class FLATLINE_API UStateBase : public UObject
{
	GENERATED_BODY()
public:
	virtual void OnStateEnter();
	virtual void OnStateUpdate();
	virtual void OnStateExit();
};

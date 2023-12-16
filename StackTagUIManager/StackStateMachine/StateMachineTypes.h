#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "StateMachineTypes.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum EStackAction
{
	Push,
	Pop
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStateEnterSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStateExitSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStackStatePushPopSignature, TScriptInterface<IStackStateInterface>,
											State);

DECLARE_LOG_CATEGORY_EXTERN(LogStateMachine, Log, All)

DECLARE_LOG_CATEGORY_EXTERN(LogStackStateMachine, Log, All)
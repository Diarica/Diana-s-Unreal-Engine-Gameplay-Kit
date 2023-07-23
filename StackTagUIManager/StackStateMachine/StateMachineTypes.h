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


UCLASS()
class FLATLINE_API UStateMachineTypes : public UObject
{
	GENERATED_BODY()
};

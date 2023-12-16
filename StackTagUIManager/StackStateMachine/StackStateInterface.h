#pragma once

#include "CoreMinimal.h"
#include "StateMachineTypes.h"
#include "UObject/Interface.h"
#include "StackStateInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(meta=(CannotImplementInterfaceInBlueprint))
class UStackStateInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FLATCORE_API IStackStateInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void EnterState(EStackAction StackAction) = 0;
	virtual void ExitState(EStackAction StackAction) = 0;
};

#pragma once

#include "CoreMinimal.h"
#include "StackStateInterface.h"
#include "UObject/Object.h"
#include "StackState.generated.h"


/**
 * 
 */
UCLASS()
class UStackState : public UObject, public IStackStateInterface
{
	GENERATED_BODY()

	virtual void EnterState(EStackAction StackAction) override;
	virtual void ExitState(EStackAction StackAction) override;


public:
	//Blueprint
	UFUNCTION(BlueprintImplementableEvent, Category="StackState", meta=(DisplayName = "OnEnterState"))
	void ReceiveEnterState(EStackAction StackAction);

	UFUNCTION(BlueprintImplementableEvent, Category="StackState", meta=(DisplayName = "OnExitState"))
	void ReceiveExitState(EStackAction StackAction);


};

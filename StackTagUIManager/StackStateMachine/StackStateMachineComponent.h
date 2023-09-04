#pragma once

#include "CoreMinimal.h"
#include "StackStateInterface.h"
#include "Components/ActorComponent.h"
#include "StackStateMachineComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStackStatePushPopSignature, TScriptInterface<IStackStateInterface>,
                                            State);

DECLARE_LOG_CATEGORY_EXTERN(LogStateMachine, Log, All)

DECLARE_LOG_CATEGORY_EXTERN(LogStackStateMachine, Log, All)

UCLASS(BlueprintType, Blueprintable,
	meta=(BlueprintSpawnableComponen, ShortTooltip =
		"StateStateMachineComponent,Can Use in Any Actor"))
class UStackStateMachineComponent : public UActorComponent, public IStackStateInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UStackStateMachineComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:

	UFUNCTION(BlueprintCallable, Category="StackStateMachine")
	void PushState(TScriptInterface<IStackStateInterface> NewState);

	UFUNCTION(BlueprintCallable, Category="StackStateMachine")
	void PopState();

	UFUNCTION(BlueprintCallable, Category="StackStateMachine")
	void PopStates(int Count);

	UFUNCTION(BlueprintCallable, Category="StackStateMachine")
	void PopAllStates();

	virtual void EnterState(EStackAction StackAction) override;
	virtual void ExitState(EStackAction StackAction) override;

	UFUNCTION(BlueprintImplementableEvent, Category="StackStateMachine", meta=(DIsplayName = "OnEnterState"))
	void ReceiveEnterState(EStackAction StackAction);

	UFUNCTION(BlueprintImplementableEvent, Category="StackStateMachine", meta=(DIsplayName = "OnExitState"))
	void ReceiveExitState(EStackAction StackAction);

	UFUNCTION(BlueprintImplementableEvent, Category="StackStateMachine", meta=(DisplayName = "StatePushed"))
	void ReceiveStatePushed(const TScriptInterface<IStackStateInterface>& PushedState);

	UFUNCTION(BlueprintImplementableEvent, Category="StackStateMachine", meta=(DisplayGame= "StatePushed"))
	void ReceiveStatePopped(const TScriptInterface<IStackStateInterface>& PoppedState);


	UPROPERTY(BlueprintAssignable, Category="StackStateMachine")
	FOnStateEnterSignature OnStateEnter;

	UPROPERTY(BlueprintAssignable, Category="StackStateMachine")
	FOnStateExitSignature OnStateExit;

	UPROPERTY(BlueprintAssignable, Category="StackStateMachine")
	FOnStackStatePushPopSignature OnStatePushed;

	UPROPERTY(BlueprintAssignable, Category="StackStateMachine")
	FOnStackStatePushPopSignature OnStatePopped;


	//Getter & Setter
	UFUNCTION(BlueprintPure, Category="StackStateMachine")
	TScriptInterface<IStackStateInterface> GetCurrentState() { return States[StateCount() - 1]; }

	UFUNCTION(BlueprintPure, Category="StackStateMachine")
	TScriptInterface<IStackStateInterface> GetUnderState() { return States[StateCount() - 2]; }

	UFUNCTION(BlueprintPure, Category="StackStateMachine")
	TScriptInterface<IStackStateInterface> GetState(int32 Index) { return States[Index]; }


	UFUNCTION(BlueprintPure, Category="StackStateMachine")
	int32 StateCount() const { return States.Num(); }

	UFUNCTION(BlueprintPure, Category="StackStateMachine")
	FORCEINLINE float GetCurrentStateTime() const { return CurrentStateTime; }

protected:
	virtual void StatePushed(TScriptInterface<IStackStateInterface> PushedState);
	virtual void StatePopped(TScriptInterface<IStackStateInterface> PoppedState);

	/* ALL STACK STATES */
	TArray<TScriptInterface<IStackStateInterface>> States;

	UPROPERTY(VisibleAnywhere)
	float CurrentStateTime = 0;
};

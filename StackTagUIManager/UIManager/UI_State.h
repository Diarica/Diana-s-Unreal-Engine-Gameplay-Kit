// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FLATCore/Framework/StackStateMachine/StackStateInterface.h"
#include "UObject/Object.h"
#include "UI_State.generated.h"




/**
 * 
 */
UCLASS()
class FLATCORE_API UUI_State : public UUserWidget,public IStackStateInterface
{
	GENERATED_BODY()


	virtual void EnterState(EStackAction StackAction) override;
	virtual void ExitState(EStackAction StackAction) override;
public:

	virtual void OnReceivePlayerStateReplicated(APawn* Pawn);
	virtual void InitUIState();

	virtual void BeginDestroy() override;

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override; 

	virtual void FinishDestroy() override;
	

	UFUNCTION(BlueprintImplementableEvent)
	void K2_InitUIState();
	
	UFUNCTION(BlueprintNativeEvent)
	void K2_OnStateEnter(EStackAction StackAction);

	UFUNCTION(BlueprintNativeEvent)
	void K2_OnStateExit(EStackAction StackAction);
	
};

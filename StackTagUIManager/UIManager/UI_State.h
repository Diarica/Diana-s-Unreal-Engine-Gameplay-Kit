// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FLATLINE/FLATLINECore/Framework/StackStateMachine/StackStateInterface.h"
#include "UObject/Object.h"
#include "FLATLINE/FLATLINECore/Framework/GameplayMessageProcessor/GameplayMessageProcessor.h"
#include "UI_State.generated.h"



class UGameplayMessageProcessor;
/**
 * 
 */
UCLASS()
class FLATLINE_API UUI_State : public UUserWidget,public IStackStateInterface
{
	GENERATED_BODY()


	virtual void EnterState(EStackAction StackAction) override;
	virtual void ExitState(EStackAction StackAction) override;
public:

	
	virtual void InitUIState(UGameplayMessageProcessor* Processor);

	virtual void BeginDestroy() override;

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override; 

	virtual void FinishDestroy() override;
	

	UFUNCTION(BlueprintImplementableEvent)
	void K2_InitUIState(UGameplayMessageProcessor* Processor);
	
	UFUNCTION(BlueprintNativeEvent)
	void K2_OnStateEnter(EStackAction StackAction);

	UFUNCTION(BlueprintNativeEvent)
	void K2_OnStateExit(EStackAction StackAction);

protected:
	UPROPERTY()
	UGameplayMessageProcessor* CachedMessageProcessor;

	
	TArray<FLocalMessageListenerHandle> ListenerHandles;
};

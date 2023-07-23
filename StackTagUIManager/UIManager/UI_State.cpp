// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_State.h"

#include "FLATLINE/FLATLINECore/Framework/GameplayMessageProcessor/GameplayMessageProcessor.h"

void UUI_State::EnterState(EStackAction StackAction)
{
	K2_OnStateEnter(StackAction);
	
}

void UUI_State::ExitState(EStackAction StackAction)
{
	K2_OnStateExit(StackAction);
}

void UUI_State::InitUIState(UGameplayMessageProcessor* Processor)
{
	check(Processor)
	CachedMessageProcessor = Processor;
	K2_InitUIState(Processor);
}

void UUI_State::BeginDestroy()
{
	Super::BeginDestroy();


}

void UUI_State::NativeConstruct()
{
	Super::NativeConstruct();
	
}

void UUI_State::NativeDestruct()
{
	Super::NativeDestruct();

}

void UUI_State::FinishDestroy()
{
	Super::FinishDestroy();
	
	/*for (const auto& Element : ListenerHandles)
	{
		CachedMessageProcessor->UnregisterListener(Element);
	}*/
}

void UUI_State::K2_OnStateEnter_Implementation(EStackAction StackAction)
{
	if(StackAction == EStackAction::Push)
	{
		
		AddToViewport();
		
	}
	else
	if(StackAction == EStackAction::Pop)
	{
		SetVisibility(ESlateVisibility::Visible);
	}
	

}

void UUI_State::K2_OnStateExit_Implementation(EStackAction StackAction)
{
	if(StackAction == EStackAction::Push)
	{
		SetVisibility(ESlateVisibility::Hidden);
		
	}
	else
	if(StackAction == EStackAction::Pop)
	{
		RemoveFromParent();
		
	}


}

// Fill out your copyright notice in the Description page of Project Settings.

#include "UserInterfaceManager.h"
#include "GameFramework/PlayerController.h"

#include "FLATLINE/FLATLINECore/Framework/UIManager/UI_State.h"
#include "Blueprint/UserWidget.h"
#include "FLATLINE/FLATLINECore/Framework/GameplayLibHatsuneMiku.h"
#include "FLATLINE/FLATLINECore/Framework/GameplayMessageProcessor/GameplayMessageProcessor.h"

void UUserInterfaceManager::InitUIStates_Implementation()
{
	check(GetOwner())
	APlayerController* PlayerController = CastChecked<APlayerController>(GetOwner());

	
	
	for (auto& Element : StatesToInitialize)
	{
		check(Element.Value)
		if(!Element.Key.IsValid())
		{
			return;
		}

		
		UUI_State* State = CreateWidget<UUI_State>(PlayerController,Element.Value);
		check(State)
		
		UIInstances.Add(Element.Key,State);
		State->SetOwningPlayer(PlayerController);
		State->InitUIState(GetOwner()->FindComponentByClass<UGameplayMessageProcessor>());

		
	}
}

UUserInterfaceManager::UUserInterfaceManager()
{
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.SetTickFunctionEnable(false);
}

UUI_State* UUserInterfaceManager::GetUI(FGameplayTag Tag)
{
	if(UUI_State** StatePointer = UIInstances.Find(Tag))
	{
		if(*StatePointer)
		{
			return *StatePointer;
		}
	}
	return nullptr;
}

void UUserInterfaceManager::PushUIState(FGameplayTag StateTag)
{
	if(!StateTag.IsValid())
	{
		return;
	}
	
	if(UUI_State* UI = GetUI(StateTag))
	{
		TScriptInterface<IStackStateInterface> Interface(UI);
		PushState(UI);
	}
}

void UUserInterfaceManager::BeginPlay()
{
	Super::BeginPlay();
	if(Cast<APlayerController>(GetOwner())->IsLocalController())
	{
		InitUIStates();
	}
}

void UUserInterfaceManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

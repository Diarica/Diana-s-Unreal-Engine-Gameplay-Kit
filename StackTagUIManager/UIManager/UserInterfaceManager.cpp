// Fill out your copyright notice in the Description page of Project Settings.

#include "UserInterfaceManager.h"

#include "UI_State.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "GameplayMessageRuntime/GameplayMessageProcessor.h"

void UUserInterfaceManager::InitUIStates()
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
		State->InitUIState();

		
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
}

void UUserInterfaceManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void UUserInterfaceManager::OnControllerPlayerStateReplicated(APawn* Pawn)
{
	for (const auto& Element : UIInstances)
	{
		Element.Value->OnReceivePlayerStateReplicated(Pawn);
	}
}

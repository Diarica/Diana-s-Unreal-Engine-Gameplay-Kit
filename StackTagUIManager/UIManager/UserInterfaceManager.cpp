// Fill out your copyright notice in the Description page of Project Settings.

#include "UserInterfaceManager.h"

#include "UI_State.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "GameplayMessageRuntime/GameplayMessageProcessor.h"

UUserInterfaceManager::UUserInterfaceManager()
{
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.SetTickFunctionEnable(false);
}


void UUserInterfaceManager::InitUIStates()
{
	check(GetOwner())
	

	
	
	for (auto& Element : StatesToInitialize)
	{
		check(Element.Value)
		if(!Element.Key.IsValid())
		{
			return;
		}

		AddUIState(Element.Key,Element.Value);
		
	}
}

bool UUserInterfaceManager::AddUIState(FGameplayTag Tag, TSubclassOf<UUI_State> StateClass)
{
	if(Tag.IsValid() == false || StateClass == nullptr)
	{
		return false;
	}
	APlayerController* PlayerController = CastChecked<APlayerController>(GetOwner());
	
	UUI_State* State = CreateWidget<UUI_State>(PlayerController,StateClass);
	check(State)
		
	UIInstancesMap.Add(Tag,State);
	State->SetOwningPlayer(PlayerController);
	State->InitUIState();

	return true;
	
}

bool UUserInterfaceManager::RemoveUIState(FGameplayTag Tag)
{
	if(const auto* InstancePtr = UIInstancesMap.Find(Tag))
	{
		auto* Ins = *InstancePtr;
		Ins->RemoveFromParent();
		UIInstancesMap.Remove(Tag);
		return true;
	}
	return false;
}



UUI_State* UUserInterfaceManager::GetUI(FGameplayTag Tag)
{
	if(UUI_State** StatePointer = UIInstancesMap.Find(Tag))
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


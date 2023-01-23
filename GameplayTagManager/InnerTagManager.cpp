// Fill out your copyright notice in the Description page of Project Settings.


#include "InnerTagManager.h"

#include "FLATLINE/FLATLINECore/GameplayTag/FlatGameplayTag.h"


// Sets default values for this component's properties
UInnerTagManager::UInnerTagManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.SetTickFunctionEnable(false);

	// ...
}

void UInnerTagManager::AddInnerTag(FGameplayTag InnerTag)
{
	if(InnerTagContainer.HasTagExact(InnerTag))
	{
		return;
	}

	const FGameplayTag InnerParentTag = InnerTagSample.RequestDirectParent();
	if(InnerTag.RequestDirectParent().MatchesTagExact(InnerParentTag))
	{
		InnerTagContainer.AddTag(InnerTag);
		OnInnerTagAdded.Broadcast(InnerTag);
	}
	
}

bool UInnerTagManager::HasInnerTag(FGameplayTag InnerTag)
{
	return InnerTagContainer.HasTagExact(InnerTag);
}

void UInnerTagManager::RemoveInnerTag(FGameplayTag InnerTag)
{
	if(InnerTagContainer.HasTagExact(InnerTag))
	{
		InnerTagContainer.RemoveTag(InnerTag);
		OnInnerTagRemoved.Broadcast(InnerTag);
	}
}


// Called when the game starts
void UInnerTagManager::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

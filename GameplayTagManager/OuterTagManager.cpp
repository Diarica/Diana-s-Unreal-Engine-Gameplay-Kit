// Fill out your copyright notice in the Description page of Project Settings.


#include "OuterTagManager.h"

#include "FLATLINE/FLATLINECore/GameplayTag/FlatGameplayTag.h"


// Sets default values for this component's properties
UOuterTagManager::UOuterTagManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.SetTickFunctionEnable(false);

	// ...
}

void UOuterTagManager::AddOuterTag(FGameplayTag OuterTag)
{
	if(WeaponOuterTagContainer.HasTagExact(OuterTag))
{
	return;
}

	
	const FGameplayTag OuterParentTag = OuterTagSample.RequestDirectParent();
	if(OuterTag.RequestDirectParent().MatchesTagExact(OuterParentTag))
	{
		WeaponOuterTagContainer.AddTag(OuterTag);
		OnOuterTagAdded.Broadcast(OuterTag);
	}
	
}

bool UOuterTagManager::HasOuterTag(FGameplayTag OuterTag)
{
	return WeaponOuterTagContainer.HasTagExact(OuterTag);
	
	
}

void UOuterTagManager::RemoveOuterTag(FGameplayTag OuterTag)
{
	if(WeaponOuterTagContainer.HasTagExact(OuterTag))
	{
		WeaponOuterTagContainer.RemoveTag(OuterTag);
		OnOuterTagRemoved.Broadcast(OuterTag);
	}
	 
	
}

void UOuterTagManager::RemoveAllOuterTags()
{
	WeaponOuterTagContainer.Reset();
}


// Called when the game starts
void UOuterTagManager::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}
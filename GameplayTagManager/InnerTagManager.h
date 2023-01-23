// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "InnerTagManager.generated.h"


DECLARE_MULTICAST_DELEGATE_OneParam(FOnInnerTagAdded,FGameplayTag)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnInnerTagRemoved,FGameplayTag)

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FLATLINE_API UInnerTagManager : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInnerTagManager();

	FGameplayTag InnerTagSample;
	
	void AddInnerTag(FGameplayTag InnerTag);

	bool HasInnerTag(FGameplayTag InnerTag);

	void RemoveInnerTag(FGameplayTag InnerTag);

	FOnInnerTagAdded OnInnerTagAdded;
	FOnInnerTagRemoved OnInnerTagRemoved;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
private:
	FGameplayTagContainer InnerTagContainer;
	
};

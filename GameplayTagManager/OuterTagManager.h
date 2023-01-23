// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "OuterTagManager.generated.h"



DECLARE_MULTICAST_DELEGATE_OneParam(FOnOuterTagAdded,FGameplayTag)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnOuterTagRemoved,FGameplayTag)

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FLATLINE_API UOuterTagManager : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UOuterTagManager();

	FGameplayTag OuterTagSample;

	void AddOuterTag(FGameplayTag OuterTag);

	bool HasOuterTag(FGameplayTag OuterTag);

	void RemoveOuterTag(FGameplayTag OuterTag);

	void RemoveAllOuterTags();
	//Call on OnOwnerChanged


	FOnOuterTagAdded OnOuterTagAdded;
	FOnOuterTagRemoved OnOuterTagRemoved;



protected:
	// Called when the game starts
	virtual void BeginPlay() override;
private:
	FGameplayTagContainer WeaponOuterTagContainer;
};

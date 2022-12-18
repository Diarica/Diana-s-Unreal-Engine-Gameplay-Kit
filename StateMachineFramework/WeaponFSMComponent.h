// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FSMComponent.h"
#include "Components/ActorComponent.h"
#include "WeaponFSMComponent.generated.h"
UENUM()
enum class EWeaponState
{
	EWS_UnOccupied = 0,
	EWS_Fire = 1,
	EWS_Reload = 2,
	EWS_Swap = 3,
	EWS_TryFire = 4,
	EWS_ColdDown = 5,
	
};


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FLATLINE_API UWeaponFSMComponent : public UFSMComponent
{
	
	GENERATED_BODY()
	
	EWeaponState CurrentStateType;
	
public:
	// Sets default values for this component's properties
	UWeaponFSMComponent();

	
	EWeaponState GetCurrentState();

	void SetCurrentState(EWeaponState StateToSet);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
};

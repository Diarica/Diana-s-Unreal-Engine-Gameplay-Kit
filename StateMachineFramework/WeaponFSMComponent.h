// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FSMComponent.h"
#include "Components/ActorComponent.h"
#include "WeaponStateBase.h"
#include "WeaponFSMComponent.generated.h"
UENUM()
enum class EWeaponState
{
	EWS_UnOccupied,
	EWS_Fire,
	EWS_Reload,
	EWS_Swap,
	EWS_TryFire
	
};


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FLATLINE_API UWeaponFSMComponent : public UFSMComponent
{
	
	GENERATED_BODY()

	
	TMap<EWeaponState,UWeaponStateBase*> StateMap;

	EWeaponState CurrentState;
	
public:
	// Sets default values for this component's properties
	UWeaponFSMComponent();
	
	EWeaponState GetCurrentState();

	void SetCurrentState(EWeaponState StateToSet);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
};

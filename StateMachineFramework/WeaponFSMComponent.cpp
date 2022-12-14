// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponFSMComponent.h"

#include "WeaponBase.h"
#include "WeaponStateBase.h"
#include "WeaponStates/WeaponState_Fire.h"
#include "WeaponStates/WeaponState_Reload.h"
#include "WeaponStates/WeaponState_Swap.h"
#include "WeaponStates/WeaponState_UnOccupied.h"


// Sets default values for this component's properties
UWeaponFSMComponent::UWeaponFSMComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

EWeaponState UWeaponFSMComponent::GetCurrentState()
{
	return CurrentState;
}

void UWeaponFSMComponent::SetCurrentState(EWeaponState StateToSet)
{
	CurrentState = StateToSet;
	SwitchState(StateMap[StateToSet]);
}


// Called when the game starts
void UWeaponFSMComponent::BeginPlay()
{
	Super::BeginPlay();


	AWeaponBase* _owner = Cast<AWeaponBase>(GetOwner());
	if(GetOwner() == _owner)
	{
		UWeaponState_UnOccupied * UnOccupied = NewObject<UWeaponState_UnOccupied>(this);
		UWeaponState_Fire * Fire = NewObject<UWeaponState_Fire>(this);
		UWeaponState_Reload * Reload = NewObject<UWeaponState_Reload>(this);
		UWeaponState_Swap * SwapWeapon = NewObject<UWeaponState_Swap>(this);

		UnOccupied->Initialize(_owner);
		Fire->Initialize(_owner);
		Reload->Initialize(_owner);
		SwapWeapon->Initialize(_owner);
		


		
		StateMap.Add(EWeaponState::EWS_UnOccupied,UnOccupied);
		StateMap.Add(EWeaponState::EWS_Fire,Fire);
		StateMap.Add(EWeaponState::EWS_Reload,Reload);
		StateMap.Add(EWeaponState::EWS_Swap,SwapWeapon);

		UKismetSystemLibrary::PrintString(GetWorld(),FString::FromInt(StateMap.Num()));
		
		SwitchOn(StateMap[EWeaponState::EWS_UnOccupied]);
	}

	
	
	
}


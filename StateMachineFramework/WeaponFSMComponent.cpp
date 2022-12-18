// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponFSMComponent.h"

#include "WeaponBase.h"
#include "WeaponStateBase.h"
#include "WeaponStates/WeaponState_ColdDown.h"
#include "WeaponStates/WeaponState_Fire.h"
#include "WeaponStates/WeaponState_Reload.h"
#include "WeaponStates/WeaponState_Swap.h"
#include "WeaponStates/WeaponState_TryFire.h"
#include "WeaponStates/WeaponState_UnOccupied.h"




// Sets default values for this component's properties
UWeaponFSMComponent::UWeaponFSMComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

EWeaponState UWeaponFSMComponent::GetCurrentState()
{
	return CurrentStateType;
}

void UWeaponFSMComponent::SetCurrentState(EWeaponState StateToSet)
{

	
	CurrentStateType = StateToSet;
	
	SwitchState(static_cast<int>(StateToSet));

	const FString WeaponFSMSpecifier = "Weapon State Machine : ";
	
	GEngine->AddOnScreenDebugMessage(0,5.0f,FColor::Yellow,WeaponFSMSpecifier + UEnum::GetValueAsString(CurrentStateType));
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
		UWeaponState_TryFire * TryFire = NewObject<UWeaponState_TryFire>(this);
		UWeaponState_ColdDown * ColdDown = NewObject<UWeaponState_ColdDown>(this);

		UnOccupied->Initialize(_owner);
		Fire->Initialize(_owner);
		Reload->Initialize(_owner);
		SwapWeapon->Initialize(_owner);
		TryFire->Initialize(_owner);
		ColdDown->Initialize(_owner);
		


		
		AddState(static_cast<int>(EWeaponState::EWS_UnOccupied),UnOccupied);
		AddState(static_cast<int>(EWeaponState::EWS_Fire),Fire);
		AddState(static_cast<int>(EWeaponState::EWS_Reload),Reload);
		AddState(static_cast<int>(EWeaponState::EWS_Swap),SwapWeapon);
		AddState(static_cast<int>(EWeaponState::EWS_TryFire),TryFire);
		AddState(static_cast<int>(EWeaponState::EWS_ColdDown),ColdDown);
		
		SwitchOn(static_cast<int>(EWeaponState::EWS_UnOccupied));
	}

	
	
	
}


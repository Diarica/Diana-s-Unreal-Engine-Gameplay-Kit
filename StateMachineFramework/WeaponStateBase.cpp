// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponStateBase.h"

#include "WeaponBase.h"

void UWeaponStateBase::Initialize(AWeaponBase* _ownerWeapon)
{
	OwnerWeapon = _ownerWeapon;
}

void UWeaponStateBase::OnStateEnter()
{
	if(OwnerWeapon == nullptr)
	{
		return;
	}
}

void UWeaponStateBase::OnStateUpdate()
{
	if(OwnerWeapon == nullptr)
	{
		return;
	}
}

void UWeaponStateBase::OnStateExit()
{
	if(OwnerWeapon == nullptr)
	{
		return;
	}
}

ACharacterBase* UWeaponStateBase::GetOwningCharacter()
{
	if(OwnerWeapon)
	{
		return OwnerWeapon->GetOwnerCharacter();
	}
	return nullptr;
}

APlayerControllerBase* UWeaponStateBase::GetOwingController()
{
	if(OwnerWeapon)
	{
		return OwnerWeapon->GetOwnerController();
		
	}
	return nullptr;
}

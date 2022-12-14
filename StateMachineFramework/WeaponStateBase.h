// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateMachineFramework/StateBase.h"
#include "UObject/Object.h"
#include "WeaponStateBase.generated.h"

class AWeaponBase;
/**
 * 
 */
UCLASS()
class FLATLINE_API UWeaponStateBase : public UStateBase
{
	GENERATED_BODY()
protected:
	UPROPERTY()
	AWeaponBase * OwnerWeapon;


public:
	void Initialize(AWeaponBase * _ownerWeapon);
	virtual void OnStateEnter() override;
	virtual void OnStateUpdate() override;
	virtual void OnStateExit() override;

	class ACharacterBase * GetOwningCharacter();
	class APlayerControllerBase * GetOwingController();

	
	

	
};

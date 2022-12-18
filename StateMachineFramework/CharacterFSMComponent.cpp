// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterFSMComponent.h"

#include "CharacterStates/CharacterState_Crouch.h"
#include "CharacterStates/CharacterState_Idle.h"
#include "CharacterStates/CharacterState_Jump.h"
#include "CharacterStates/CharacterState_Sprint.h"
#include "CharacterStates/CharacterState_Walk.h"


// Sets default values for this component's properties
UCharacterFSMComponent::UCharacterFSMComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

EMovementState UCharacterFSMComponent::GetCurrentState() const
{
	return CurrentStateType;
}

void UCharacterFSMComponent::SetCurrentState(EMovementState State)
{
	CurrentStateType = State;
	SwitchState(static_cast<int>(State));
}


// Called when the game starts
void UCharacterFSMComponent::BeginPlay()
{
	Super::BeginPlay();

	ACharacterBase * _owner = Cast<ACharacterBase>(GetOwner());
	if(_owner == GetOwner())
	{
		UCharacterState_Idle * Idle = NewObject<UCharacterState_Idle>(this);
		UCharacterState_Walk * Walk = NewObject<UCharacterState_Walk>(this);
		UCharacterState_Crouch * Crouch = NewObject<UCharacterState_Crouch>(this);
		UCharacterState_Jump * Jump = NewObject<UCharacterState_Jump>(this);
		UCharacterState_Sprint * Sprint = NewObject<UCharacterState_Sprint>(this);

		Idle->Initialization(_owner);
		Walk->Initialization(_owner);
		Crouch->Initialization(_owner);
		Jump->Initialization(_owner);
		Sprint->Initialization(_owner);

		AddState(static_cast<int>(EMovementState::EMS_Idle),Idle);
		AddState(static_cast<int>(EMovementState::EMS_Walk),Walk);
		AddState(static_cast<int>(EMovementState::EMS_Crouch),Crouch);
		AddState(static_cast<int>(EMovementState::EMS_Jump),Jump);
		AddState(static_cast<int>(EMovementState::EMS_Sprint),Sprint);

		SwitchOn(static_cast<int>(EMovementState::EMS_Idle));
		
		
	}

	// ...
	
}


// Called every frame
void UCharacterFSMComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                           FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// ...
}


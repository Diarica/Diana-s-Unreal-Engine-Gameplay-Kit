// Fill out your copyright notice in the Description page of Project Settings.


#include "FSMComponent.h"


// Sets default values for this component's properties
UFSMComponent::UFSMComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UFSMComponent::SwitchState(UStateBase* newState)
{
	if(newState)
	{
		CurrentState->OnStateExit();
		SwitchOn(newState);
	}
}


// Called when the game starts
void UFSMComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UFSMComponent::SwitchOn(UStateBase* newState)
{
	if(newState)
	{
		CurrentState = newState;
		if(CurrentState)
		CurrentState->OnStateEnter();
	}
}


// Called every frame
void UFSMComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if(CurrentState)
	{
		CurrentState->OnStateUpdate();
	}
	// ...
}


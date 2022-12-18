// Fill out your copyright notice in the Description page of Project Settings.


#include "FSMComponent.h"

#include "Kismet/KismetSystemLibrary.h"


// Sets default values for this component's properties
UFSMComponent::UFSMComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UFSMComponent::SwitchState(int newStateID)
{
	if(StatesMap[newStateID] != nullptr)
	{
		if(CurrentState)
		{
			CurrentState->OnStateExit();
		}
	
		SwitchOn(newStateID);
	
	}
}

void UFSMComponent::AddState(int ID, UStateBase* StateClass)
{
	if(StateClass)
	{
		for (auto &Element : StatesMap)
		{
			if(Element.Key == ID)
			{
				UKismetSystemLibrary::PrintWarning("State ID HAS TWO SAME");
				break;
			}
		}
	}
	
	StatesMap.Add(ID,StateClass);
}


// Called when the game starts
void UFSMComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UFSMComponent::SwitchOn(int newStateID)
{
	if(StatesMap[newStateID] != nullptr)
	{
		CurrentState = StatesMap[newStateID];
		if(CurrentState)
			CurrentState->OnStateEnter();
		CurrentStateID = newStateID;
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


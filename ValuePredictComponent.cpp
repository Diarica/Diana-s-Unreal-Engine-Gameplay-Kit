// Fill out your copyright notice in the Description page of Project Settings.


#include "ValuePredictComponent.h"

#include "Kismet/KismetSystemLibrary.h"


////
///COMP MUST REP!

// Sets default values for this component's properties
UValuePredictComponent::UValuePredictComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicated(true);
	// ...
}



void UValuePredictComponent::ReduceValue(int ValueToReduce,int MaxValue)
{
	if(ValueToReduce == 0 || MaxValue == 0)
	{
		return;
	}
	if(ValueToReduce > MaxValue)
	{
		ValueToReduce = MaxValue;
	}
	
	CurrentValue = FMath::Clamp(CurrentValue-ValueToReduce,0,MaxValue);

	/*梓铭小哥哥*/
	/*大好きだよ*/

	if(OnValueChange.IsBound())
	{
		OnValueChange.Execute(CurrentValue);
	}
	
	if(GetOwner()->HasAuthority())
	{
		ClientUpdateValue(CurrentValue);
	}
	else
	{
		++Sequence;
	}
	
}

void UValuePredictComponent::AddValue(int ValueToAdd,int MaxValue)
{
	if(ValueToAdd > MaxValue  || ValueToAdd == 0)
	{
		return;
	}
	
	CurrentValue = FMath::Clamp(CurrentValue + ValueToAdd,0,MaxValue);
	//TODO SET HUD

	ClientAddValue(ValueToAdd,MaxValue);
	if(OnValueChange.IsBound())
	{
		OnValueChange.Execute(CurrentValue);
	}
}


void UValuePredictComponent::ClientUpdateValue_Implementation(int ServerAmmo)
{
	if(GetOwner()->HasAuthority())return;
	CurrentValue = ServerAmmo;
	--Sequence;
	CurrentValue-=Sequence;
	
	if(OnValueChange.IsBound())
	{
		OnValueChange.Execute(CurrentValue);
	}
	
}
void UValuePredictComponent::ClientAddValue_Implementation(int AmmoToAdd, int AmmoInMag)
{
	if(GetOwner()->HasAuthority())return;
	CurrentValue = FMath::Clamp(CurrentValue + AmmoToAdd,0,AmmoInMag);
	if(OnValueChange.IsBound())
	{
		OnValueChange.Execute(CurrentValue);
	}
}


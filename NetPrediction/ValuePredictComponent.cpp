#include "ValuePredictComponent.h"




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


void UValuePredictComponent::ReduceValue(int ReduceVal, int MaxValue)
{
	CurrentValue = FMath::Clamp(CurrentValue - ReduceVal, 0, MaxValue);

	//CLient Side Prediction

	if (OnValueChange.IsBound())
	{
		OnValueChange.Execute(CurrentValue);
	}

	if (GetOwner()->HasAuthority())
	{
		ClientUpdateValue(CurrentValue,ReduceVal,MaxValue);
	}
	else
	{
		FValueUpdateData ValueUpdateData;
		ValueUpdateData.ValueDelta = ReduceVal;
		
		ValueUpdateDatas.Add(ValueUpdateData);
	}
}

void UValuePredictComponent::AddValue(int ValueToAdd, int MaxValue)
{
	
	CurrentValue = FMath::Clamp(CurrentValue + ValueToAdd, 0, MaxValue);

	//CLient Side Prediction

	if (OnValueChange.IsBound())
	{
		OnValueChange.Execute(CurrentValue);
	}

	if (GetOwner()->HasAuthority())
	{
		ClientUpdateValue(CurrentValue,ValueToAdd,MaxValue);
	}
	else
	{
		FValueUpdateData ValueUpdateData;
		ValueUpdateData.ValueDelta = ValueToAdd;
		
		ValueUpdateDatas.Add(ValueUpdateData);
	}
}


void UValuePredictComponent::ClientUpdateValue_Implementation(int ServerAmmo, int ValueDelta, int MaxVal)
{
	if (GetOwner()->HasAuthority())
	{
		return;
	}
	CurrentValue = ServerAmmo;

	int TotalValueDelta = 0;

	for (int i = 0; i < ValueUpdateDatas.Num(); i++)
	{
		TotalValueDelta += ValueUpdateDatas[i].ValueDelta;

		if (ValueUpdateDatas[i].ValueDelta == ValueDelta)
		{
			TotalValueDelta -= ValueDelta;
			ValueUpdateDatas.RemoveAt(i);
			i--;
		}
	}

	CurrentValue = FMath::Clamp(CurrentValue+TotalValueDelta,0,MaxVal);

	if (OnValueChange.IsBound())
	{
		OnValueChange.Execute(CurrentValue);
	}
}

void UValuePredictComponent::ClientAddValue_Implementation(int AmmoToAdd, int AmmoInMag)
{
	if (GetOwner()->HasAuthority())
	{
		return;
	}
	CurrentValue = FMath::Clamp(CurrentValue + AmmoToAdd, 0, AmmoInMag);
	if (OnValueChange.IsBound())
	{
		OnValueChange.Execute(CurrentValue);
	}
}

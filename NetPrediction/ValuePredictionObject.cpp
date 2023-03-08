#include "ValuePredictionObject.h"




////
///COMP MUST REP!

// Sets default values for this component's properties
UValuePredictionObject::UValuePredictionObject()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
}

void UValuePredictionObject::AddValueBoth(int ValToAdd, int MaxVal)
{
	AddValue(ValToAdd,MaxVal);
	SERVER_InternalAddVal(ValToAdd,MaxVal);
}

void UValuePredictionObject::ReduceValueBoth(int ValToReduce, int MaxVal)
{
	ReduceValue(ValToReduce,MaxVal);
	SERVER_InternalReduceVal(ValToReduce,MaxVal);
}

void UValuePredictionObject::SERVER_InternalAddVal_Implementation(int ValueToAdd, int MaxValue)
{
	AddValue(ValueToAdd,MaxValue);
}

void UValuePredictionObject::SERVER_InternalReduceVal_Implementation(int ReduceVal, int MaxValue)
{
	ReduceValue(ReduceVal,MaxValue);
}


void UValuePredictionObject::ReduceValue(int ReduceVal, int MaxValue)
{
	CurrentValue = FMath::Clamp(CurrentValue - ReduceVal, 0, MaxValue);

	//CLient Side Prediction

	if (OnValueChange.IsBound())
	{
		OnValueChange.Execute(CurrentValue);
	}

	if (GetActorOuter()->HasAuthority())
	{
		ClientUpdateValue(CurrentValue,ReduceVal,MaxValue);
	}
	else
	{
		FValueUpdateData ValueUpdateData;
		ValueUpdateData.ValueDelta = ReduceVal;
		
		UnProcessedValues.Add(ValueUpdateData);
	}
}

void UValuePredictionObject::AddValue(int ValueToAdd, int MaxValue)
{
	
	CurrentValue = FMath::Clamp(CurrentValue + ValueToAdd, 0, MaxValue);

	//CLient Side Prediction

	if (OnValueChange.IsBound())
	{
		OnValueChange.Execute(CurrentValue);
	}

	if (GetActorOuter()->HasAuthority())
	{
		ClientUpdateValue(CurrentValue,ValueToAdd,MaxValue);
	}
	else
	{
		FValueUpdateData ValueUpdateData;
		ValueUpdateData.ValueDelta = ValueToAdd;
		
		UnProcessedValues.Add(ValueUpdateData);
	}
}


void UValuePredictionObject::ClientUpdateValue_Implementation(int ServerAmmo, int ValueDelta, int MaxVal)
{
	if (GetActorOuter()->HasAuthority())
	{
		return;
	}
	CurrentValue = ServerAmmo;

	int TotalValueDelta = 0;

	for (int i = 0; i < UnProcessedValues.Num(); i++)
	{
		TotalValueDelta += UnProcessedValues[i].ValueDelta;

		if (UnProcessedValues[i].ValueDelta == ValueDelta)
		{
			TotalValueDelta -= ValueDelta;
			UnProcessedValues.RemoveAt(i);
			i--;
		}
	}

	CurrentValue = FMath::Clamp(CurrentValue+TotalValueDelta,0,MaxVal);

	if (OnValueChange.IsBound())
	{
		OnValueChange.Execute(CurrentValue);
	}
}

void UValuePredictionObject::ClientAddValue_Implementation(int AmmoToAdd, int AmmoInMag)
{
	if (GetActorOuter()->HasAuthority())
	{
		return;
	}
	CurrentValue = FMath::Clamp(CurrentValue + AmmoToAdd, 0, AmmoInMag);
	if (OnValueChange.IsBound())
	{
		OnValueChange.Execute(CurrentValue);
	}
}

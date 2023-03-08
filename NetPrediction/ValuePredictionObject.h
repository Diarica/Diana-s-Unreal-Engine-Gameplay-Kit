#pragma once

#include "CoreMinimal.h"
#include "Setting/NetworkObject.h"
#include "ValuePredictionObject.generated.h"
USTRUCT()
struct FValueUpdateData
{
	GENERATED_BODY()

	int ValueDelta;

	
	
};
DECLARE_DELEGATE_OneParam(FOnValueChanged, int);
UCLASS()
class UValuePredictionObject : public UNetworkObject
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UValuePredictionObject();

public:
	
	void ReduceValue(int ReduceVal, int MaxValue);
	
	void AddValue(int ValueToAdd, int MaxValue);

	//ReduceValue() and AddValue() cannot only execute on client,because you need to sync data from server
	//This UObject MUST BE REPLICATED!
private:
	UFUNCTION(Client, Reliable)
	void ClientUpdateValue(int ServerAmmo, int ValueDelta, int MaxVal);

	UFUNCTION(Client, Reliable)
	void ClientAddValue(int AmmoToAdd, int AmmoInMag);
	//The Number of unprocessed server requests value.
	//incremented in ClientUpdateValue;

private:
	UPROPERTY(BlueprintReadOnly,meta=(AllowPrivateAccess="true"))
	int CurrentValue;

TArray<FValueUpdateData> UnProcessedValues;


#pragma endregion

	FORCEINLINE int GetCurrentValue() const
	{
		return CurrentValue;
	}

	FOnValueChanged OnValueChange;
};

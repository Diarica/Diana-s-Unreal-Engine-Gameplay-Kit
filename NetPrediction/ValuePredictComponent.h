#pragma once

#include "CoreMinimal.h"
#include "ValuePredictComponent.generated.h"
USTRUCT()
struct FValueUpdateData
{
	GENERATED_BODY()

	int ValueDelta;

	
	
};
DECLARE_DELEGATE_OneParam(FOnValueChanged, int);
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UValuePredictComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UValuePredictComponent();


	void ReduceValue(int ReduceVal, int MaxValue);
	void AddValue(int ValueToAdd, int MaxValue);

private:
	UFUNCTION(Client, Reliable)
	void ClientUpdateValue(int ServerAmmo, int ValueDelta, int MaxVal);

	UFUNCTION(Client, Reliable)
	void ClientAddValue(int AmmoToAdd, int AmmoInMag);
	//The Number of unprocessed server requests value.
	//incremented in ClientUpdateValue;

public:
	UPROPERTY(BlueprintReadOnly)
	int CurrentValue;

TArray<FValueUpdateData> ValueUpdateDatas;


#pragma endregion

	FORCEINLINE int GetCurrentValue() const
	{
		return CurrentValue;
	}

	FOnValueChanged OnValueChange;
};

#pragma once

#include "CoreMinimal.h"
#include "ValuePredictComponent.generated.h"

DECLARE_DELEGATE_OneParam(FOnValueChanged, int);
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FLATLINE_API UValuePredictComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UValuePredictComponent();


	void ReduceValue(int ValueToReduce, int MaxValue);
	void AddValue(int ValueToAdd, int MaxValue);

private:
	UFUNCTION(Client, Reliable)
	void ClientUpdateValue(int ServerAmmo);

	UFUNCTION(Client, Reliable)
	void ClientAddValue(int AmmoToAdd, int AmmoInMag);
	//The Number of unprocessed server requests value.
	//incremented in ClientUpdateValue;
	int Sequence;

public:
	UPROPERTY(BlueprintReadOnly)
	int CurrentValue;
#pragma endregion

	FORCEINLINE int GetCurrentValue() const
	{
		return CurrentValue;
	}

	FOnValueChanged OnValueChange;

	FORCEINLINE bool IsValueSyncDone() const
	{
		return Sequence == 0;
	}
};

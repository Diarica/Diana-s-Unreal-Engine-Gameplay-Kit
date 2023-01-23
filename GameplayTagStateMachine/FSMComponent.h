#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

#include "Components/ActorComponent.h"

#include "FSMComponent.generated.h"

class IState;
struct FGameplayTag;
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FLATLINE_API UFSMComponent : public UActorComponent
{
	GENERATED_BODY()
	
protected:

	UPROPERTY()
	class UStateBase* CurrentStateInstance = nullptr;

	
	UPROPERTY()
	TMap<FGameplayTag, UStateBase*> StatesMap;

	FGameplayTag CurrentStateTag;

public:
	// Sets default values for this component's properties
	UFSMComponent();

	void SwitchState(FGameplayTag newStateTag);

	void AddState(FGameplayTag Tag, UStateBase* StateClass);

	FGameplayTag GetCurrentState() const
	{
		return CurrentStateTag;
	}

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void SwitchOn(FGameplayTag newStateTag);

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};

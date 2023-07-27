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
	TScriptInterface<IState> CurrentStateInstance = nullptr;
	
	UPROPERTY()
	TMap<int,TScriptInterface<IState>> StatesMap;

	int CurrentStateID;

	int StatesCount;

public:
	// Sets default values for this component's properties
	UFSMComponent();

	void SwitchState(int StateID);

	void AddState(int StateID, TScriptInterface<IState> StateClass);

	int GetCurrentStateID() const
	{
		return CurrentStateID;
	}

	virtual void InitializeFSM();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void SwitchOn(int newStateID);

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};

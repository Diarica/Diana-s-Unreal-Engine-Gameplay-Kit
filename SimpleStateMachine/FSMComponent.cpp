#include "FSMComponent.h"


#include "State.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values for this component's properties
UFSMComponent::UFSMComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UFSMComponent::SwitchState(int StateID)
{
	TScriptInterface<IState> State = StatesMap[StateID];
	if (State && State->CanEnterState())
	{
		if (CurrentStateInstance)
		{
			CurrentStateInstance->OnStateExit();
		}

		SwitchOn(StateID);
	}
}

void UFSMComponent::AddState(int StateID, TScriptInterface<IState> StateClass)
{
	if (StateClass)
	{
		for (auto& Element : StatesMap)
		{
			if (Element.Key == StateID)
			{
				UKismetSystemLibrary::PrintWarning("ERROR : State Tag HAS TWO EXACT SAME");
				break;
			}
		}
	}

	StatesMap.Add(StateID, StateClass);
	++StatesCount;
}

void UFSMComponent::InitializeFSM()
{
}

// Called when the game starts
void UFSMComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	InitializeFSM();
}

void UFSMComponent::SwitchOn(int newStateID)
{
	if (StatesMap[newStateID] != nullptr)
	{
		CurrentStateInstance = StatesMap[newStateID];
		if (CurrentStateInstance)
		{
			CurrentStateInstance->OnStateEnter();
		}
		CurrentStateID = newStateID;
	}
}


// Called every frame
void UFSMComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (CurrentStateInstance)
	{
		CurrentStateInstance->OnStateUpdate();
	}
	// ...
}

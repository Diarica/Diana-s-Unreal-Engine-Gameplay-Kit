#include "FSMComponent.h"


#include "StateBase.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values for this component's properties
UFSMComponent::UFSMComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UFSMComponent::SwitchState(FGameplayTag newStateTag)
{
	if (StatesMap[newStateTag] != nullptr)
	{
		if (CurrentStateInstance)
		{
			CurrentStateInstance->OnStateExit();
		}

		SwitchOn(newStateTag);
	}
}

void UFSMComponent::AddState(FGameplayTag Tag, UStateBase* StateClass)
{
	if (StateClass)
	{
		for (auto& Element : StatesMap)
		{
			if (Element.Key == Tag)
			{
				UKismetSystemLibrary::PrintWarning("ERROR : State Tag HAS TWO EXACT SAME");
				break;

				
			}
		}
	}

	StatesMap.Add(Tag, StateClass);
}

// Called when the game starts
void UFSMComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

void UFSMComponent::SwitchOn(FGameplayTag newStateTag)
{
	if (StatesMap[newStateTag] != nullptr)
	{
		CurrentStateInstance = StatesMap[newStateTag];
		if (CurrentStateInstance)
		{
			CurrentStateInstance->OnStateEnter();
		}
		CurrentStateTag = newStateTag;
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

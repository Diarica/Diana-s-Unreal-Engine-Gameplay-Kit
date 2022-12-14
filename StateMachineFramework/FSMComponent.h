// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateBase.h"
#include "Components/ActorComponent.h"

#include "FSMComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FLATLINE_API UFSMComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY()
	UStateBase* CurrentState = nullptr;

	

public:
	// Sets default values for this component's properties
	UFSMComponent();

	void SwitchState(UStateBase* newState);

	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void SwitchOn(UStateBase* newState);

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};

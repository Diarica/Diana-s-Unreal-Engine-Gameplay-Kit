// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterStates/CharacterStateBase.h"
#include "Components/ActorComponent.h"
#include "CharacterFSMComponent.generated.h"


enum class EMovementState : uint8;
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FLATLINE_API UCharacterFSMComponent : public UFSMComponent
{
	GENERATED_BODY()



	UPROPERTY(BlueprintReadOnly,meta=(AllowPrivateAccess = "true"))
	EMovementState CurrentStateType;


	

public:
	// Sets default values for this component's properties
	UCharacterFSMComponent();

	EMovementState GetCurrentState() const;

	void SetCurrentState(EMovementState State);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};

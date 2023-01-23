// Fill out your copyright notice in the Description page of Project Settings.


#include "TagMessageFSM.h"


// Sets default values for this component's properties
UTagMessageFSM::UTagMessageFSM()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UTagMessageFSM::ExecuteAddedInnerFuncIfTagValid(FGameplayTag InnerTag)
{
	if()
}

void UTagMessageFSM::ExecuteRemovedInnerFuncIfTagValid(FGameplayTag InnerTag)
{
}

void UTagMessageFSM::ExecuteAddedOuterFuncIfTagValid(FGameplayTag OuterTag)
{
}

void UTagMessageFSM::ExecuteRemovedOuterFuncIfTagValid(FGameplayTag OuterTag)
{
}


// Called when the game starts
void UTagMessageFSM::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UTagMessageFSM::OnReceiveOuterTagAdded(FGameplayTag OuterTagAdded)
{
	TFunctionRef<void>* FunctionRef = AddedOuterTagFunctionMap.Find(OuterTagAdded);
	
	FunctionRef();
	
}

void UTagMessageFSM::OnReceiveInnerTagAdded(FGameplayTag InnerTagAdded)
{
	AddedInnerTagFunctionMap.Find(InnerTagAdded);
}

void UTagMessageFSM::OnReceiveOuterTagRemoved(FGameplayTag OuterTagRemoved)
{
	RemovedOuterTagFunctionMap.Find(OuterTagRemoved);
}

void UTagMessageFSM::OnReceiveInnerTagRemoved(FGameplayTag InnerTagRemoved)
{
	RemovedInnerTagFunctionMap.Find(InnerTagRemoved);
}

void UTagMessageFSM::BindOuterTagAddedFunction(FGameplayTag AddedOuterTag, TFunctionRef<void> TargetFunc)
{
	if(IsOuterTag(AddedOuterTag))
	{
		AddedOuterTagFunctionMap.Add(AddedOuterTag,TargetFunc);
	}
}

void UTagMessageFSM::BindOuterTagRemovedFunction(FGameplayTag RemovedOuterTag, TFunctionRef<void> TargetFunc)
{
	if (IsOuterTag(RemovedOuterTag))
	{
		RemovedOuterTagFunctionMap.Add(RemovedOuterTag,TargetFunc);
	}
}

void UTagMessageFSM::BindInnerTagAddedFunction(FGameplayTag AddedInnerTag, TFunctionRef<void> TargetFunc)
{
	if(IsInnerTag(AddedInnerTag))
	{
		AddedInnerTagFunctionMap.Add(AddedInnerTag,TargetFunc);
	}
}

void UTagMessageFSM::BindInnerTagRemovedFunction(FGameplayTag RemovedInnerTag, TFunctionRef<void> TargetFunc)
{
	if(IsInnerTag(RemovedInnerTag))
	{
		RemovedInnerTagFunctionMap.Add(RemovedInnerTag,TargetFunc);
	}
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "TagMessageFSM.h"

#include "Kismet/KismetSystemLibrary.h"


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
	CallAddedInnerTagFunc(InnerTag);
}

void UTagMessageFSM::ExecuteRemovedInnerFuncIfTagValid(FGameplayTag InnerTag)
{
	CallRemovedInnerTagFunc(InnerTag);
}

void UTagMessageFSM::ExecuteAddedOuterFuncIfTagValid(FGameplayTag OuterTag)
{
	CallAddedOuterTagFunc(OuterTag);
}

void UTagMessageFSM::ExecuteRemovedOuterFuncIfTagValid(FGameplayTag OuterTag)
{
	CallRemovedOuterTagFunc(OuterTag);
}


// Called when the game starts
void UTagMessageFSM::BeginPlay()
{
	Super::BeginPlay();

	// ...

	if(SampleInnerTag == FGameplayTag::EmptyTag || SampleOuterTag == FGameplayTag::EmptyTag)
	{
		UKismetSystemLibrary::PrintString(GetWorld(),"Sample Inner or Outer Tag Is null");
	}
	
}

void UTagMessageFSM::OnReceiveOuterTagAdded(FGameplayTag OuterTagAdded)
{
	CallAddedOuterTagFunc(OuterTagAdded);
}

void UTagMessageFSM::OnReceiveInnerTagAdded(FGameplayTag InnerTagAdded)
{
	CallAddedInnerTagFunc(InnerTagAdded);
}

void UTagMessageFSM::OnReceiveOuterTagRemoved(FGameplayTag OuterTagRemoved)
{
	CallRemovedOuterTagFunc(OuterTagRemoved);
}

void UTagMessageFSM::OnReceiveInnerTagRemoved(FGameplayTag InnerTagRemoved)
{
	CallRemovedInnerTagFunc(InnerTagRemoved);
}

void UTagMessageFSM::BindOuterTagAddedFunction(FGameplayTag AddedOuterTag, TFunctionRef<void()> TargetFunc)
{
	if(IsOuterTag(AddedOuterTag))
	{
		AddedOuterTagFunctionMap.Add(AddedOuterTag,TargetFunc);
	}
}

void UTagMessageFSM::BindOuterTagRemovedFunction(FGameplayTag RemovedOuterTag, TFunctionRef<void()> TargetFunc)
{
	if (IsOuterTag(RemovedOuterTag))
	{
		RemovedOuterTagFunctionMap.Add(RemovedOuterTag,TargetFunc);
	}
}

void UTagMessageFSM::BindInnerTagAddedFunction(FGameplayTag AddedInnerTag, TFunctionRef<void()> TargetFunc)
{
	if(IsInnerTag(AddedInnerTag))
	{
		AddedInnerTagFunctionMap.Add(AddedInnerTag,TargetFunc);
	}
}

void UTagMessageFSM::BindInnerTagRemovedFunction(FGameplayTag RemovedInnerTag, TFunctionRef<void()> TargetFunc)
{
	if(IsInnerTag(RemovedInnerTag))
	{
		RemovedInnerTagFunctionMap.Add(RemovedInnerTag,TargetFunc);
	}
}





void UTagMessageFSM::CallAddedOuterTagFunc(FGameplayTag AddedOuterTag)
{
	&AddedOuterTagFunctionMap.Find(AddedOuterTag)();
}

void UTagMessageFSM::CallRemovedOuterTagFunc(FGameplayTag RemovedOuterTag)
{
	&RemovedOuterTagFunctionMap.Find(RemovedOuterTag)();
}

void UTagMessageFSM::CallAddedInnerTagFunc(FGameplayTag AddedInnerTag)
{
	&AddedInnerTagFunctionMap.Find(AddedInnerTag)();
}

void UTagMessageFSM::CallRemovedInnerTagFunc(FGameplayTag RemovedInnerTag)
{
	&RemovedInnerTagFunctionMap.Find(RemovedInnerTag)();
}

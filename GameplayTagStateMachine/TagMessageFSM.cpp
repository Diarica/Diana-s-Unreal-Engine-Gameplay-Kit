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

void UTagMessageFSM::BindOuterTagAddedFunction(FGameplayTag AddedOuterTag, TFunction<void()> TargetFunc)
{
	if(IsOuterTag(AddedOuterTag))
	{
		AddedOuterTagFunctionMap.Add(AddedOuterTag,TargetFunc);
	}
}

void UTagMessageFSM::BindOuterTagRemovedFunction(FGameplayTag RemovedOuterTag, TFunction<void()> TargetFunc)
{
	if (IsOuterTag(RemovedOuterTag))
	{
		RemovedOuterTagFunctionMap.Add(RemovedOuterTag,TargetFunc);
	}
}

void UTagMessageFSM::BindInnerTagAddedFunction(FGameplayTag AddedInnerTag, TFunction<void()> TargetFunc)
{
	if(IsInnerTag(AddedInnerTag))
	{
		AddedInnerTagFunctionMap.Add(AddedInnerTag,TargetFunc);
	}
}

void UTagMessageFSM::BindInnerTagRemovedFunction(FGameplayTag RemovedInnerTag, TFunction<void()> TargetFunc)
{
	if(IsInnerTag(RemovedInnerTag))
	{
		RemovedInnerTagFunctionMap.Add(RemovedInnerTag,TargetFunc);
	}
}





void UTagMessageFSM::CallAddedOuterTagFunc(FGameplayTag AddedOuterTag)
{
	if(AddedOuterTagFunctionMap.Contains(AddedOuterTag))
	{
		AddedOuterTagFunctionMap[AddedOuterTag]();
	}
}

void UTagMessageFSM::CallRemovedOuterTagFunc(FGameplayTag RemovedOuterTag)
{
	if(RemovedOuterTagFunctionMap.Contains(RemovedOuterTag))
	{
		RemovedOuterTagFunctionMap[RemovedOuterTag]();
	}
}

void UTagMessageFSM::CallAddedInnerTagFunc(FGameplayTag AddedInnerTag)
{
	if(AddedInnerTagFunctionMap.Contains(AddedInnerTag))
	{
		AddedInnerTagFunctionMap[AddedInnerTag]();
	}
	
}

void UTagMessageFSM::CallRemovedInnerTagFunc(FGameplayTag RemovedInnerTag)
{
	if(RemovedInnerTagFunctionMap.Contains(RemovedInnerTag))
	{
		RemovedInnerTagFunctionMap[RemovedInnerTag]();
	}
}

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameplayTagFunctionTable.generated.h"

USTRUCT()
struct FTagFuncStruct
{
	GENERATED_BODY()

	TFunction<void()> EnabledFunctionPtr;
	TFunction<void()> DisabledFunctionPtr;
	
};

USTRUCT()
struct FGameplayTagFunctionTable
{
	GENERATED_BODY()
private:
	TMap<FGameplayTag,FTagFuncStruct> FunctionTable;
public:
	void RegisterFuncPair(const FGameplayTag& Tag, const FTagFuncStruct& Func)
	{
		if(!Tag.IsValid())
		{
			return;
		}
	
		if(FTagFuncStruct* Pair = FunctionTable.Find(Tag))
		{
			*Pair = Func;
		}
		else
		{
			FunctionTable.Add(Tag,Func);
		}
	}

	void UnRegisterFuncPair(const FGameplayTag& Tag)
	{
		if(!Tag.IsValid())
		{
			return;
		}

		if(FunctionTable.Find(Tag))
		{
			FunctionTable.Remove(Tag);
		}
		
	}

	void CallEnabledFunc(const FGameplayTag& Tag)
	{
		const FTagFuncStruct* FuncStruct = FunctionTable.Find(Tag);

		if(FuncStruct->EnabledFunctionPtr)
		{
			FuncStruct->EnabledFunctionPtr();
		}
	}

	void CallRemovedFunc(const FGameplayTag& Tag)
	{
		const FTagFuncStruct* FuncStruct = FunctionTable.Find(Tag);

		if(FuncStruct->DisabledFunctionPtr)
		{
			FuncStruct->DisabledFunctionPtr();
		}
	}

	FTagFuncStruct* GetFuncStructPtrIfTagValid(const FGameplayTag& Tag)
	{
		if(!Tag.IsValid())
		{
			return nullptr;
		}
	
		if(FTagFuncStruct* FunctionStruct = FunctionTable.Find(Tag))
		{
			return FunctionStruct;
		}
		return nullptr;
	}

	bool HasTag(const FGameplayTag& Tag) const
	{
		return FunctionTable.Contains(Tag);
	}
	
	
};
//Tag-Function Pair Object,Only can bind a Function per Gameplay Tag

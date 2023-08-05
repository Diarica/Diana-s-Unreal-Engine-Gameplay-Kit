// Fill out your copyright notice in the Description page of Project Settings.


#include "TagScalarProp.h"


//////////////////////////////////////////////////////////////////////
// FGameplayTagScalarProperty



FString FGameplayTagScalarProperty::GetDebugString() const
{
	return FString::Printf(TEXT("%sx%d"), *Tag.ToString(),FloatScalar.GetMultiplier());
}

//////////////////////////////////////////////////////////////////////
// FGameplayTagScalarPropertyContainer

void FGameplayTagScalarPropertyContainer::AddProperty(FGameplayTag Tag, float BaseValue)
{
	if (!Tag.IsValid())
	{
		FFrame::KismetExecutionMessage(TEXT("An invalid tag was passed to AddProperty"), ELogVerbosity::Warning);
		return;
	}

	
		for (FGameplayTagScalarProperty& Property : Properties)
		{
			if (Property.Tag == Tag)
			{
				return;
			}
		}

		FGameplayTagScalarProperty& NewProperty = Properties.Emplace_GetRef(Tag, BaseValue);


	
	TagToCountMap.Add(Tag,FFloatScalar(BaseValue));
	MarkItemDirty(NewProperty);
		
	
}

FFloatScalarModiferHandle FGameplayTagScalarPropertyContainer::AddPropertyMultiplier(FGameplayTag Tag, float Multiplier)
{

	if(Tag.IsValid())
	{
		for (FGameplayTagScalarProperty& Property : Properties)
		{
			if(Property.Tag == Tag)
			{
				Property.FloatScalar.SetMultiplier(Multiplier);
				TagToCountMap[Tag] = Property.FloatScalar;


				const FFloatScalarModiferHandle Result = InternalAddPropertyMultiplier(Tag,Multiplier);
				MarkItemDirty(Property);
				return Result;
			}
		}
	}
	return FFloatScalarModiferHandle(FGameplayTag::EmptyTag,0.00);
}

bool FGameplayTagScalarPropertyContainer::RemovePropertyMultiplier(FFloatScalarModiferHandle& Handle)
{
	if(Handle.Tag.IsValid())
	{
		FGameplayTag& Tag = Handle.Tag;
		for (FGameplayTagScalarProperty& Property : Properties)
		{
			if(Property.Tag == Tag)
			{
				Property.FloatScalar.SetMultiplier(Handle.Multiplier);
				TagToCountMap[Tag] = Property.FloatScalar;

				
				InternalRemovePropertyMultiplier(Handle);
				MarkItemDirty(Property);
				return true;
			}
		}
	}
	return false;
}

void FGameplayTagScalarPropertyContainer::RemoveProperty(FGameplayTag Tag)
{
	if (!Tag.IsValid())
	{
		FFrame::KismetExecutionMessage(TEXT("An invalid tag was passed to RemoveProperty"), ELogVerbosity::Warning);
		return;
	}
	
		for (auto It = Properties.CreateIterator(); It; ++It)
		{
			FGameplayTagScalarProperty& Property = *It;
			if (Property.Tag == Tag)
			{
				It.RemoveCurrent();
				TagToCountMap.Remove(Tag);
				InternalRemoveAllMultiplier(Tag);
				MarkArrayDirty();
				return;
			}
		}
	
}

FFloatScalarModiferHandle FGameplayTagScalarPropertyContainer::InternalAddPropertyMultiplier(const FGameplayTag& Tag,
	float Multiplier)
{
	const FFloatScalarModiferHandle Handle(Tag,Multiplier);
	ModiferHandles.Add(Handle);
	return Handle;
}

bool FGameplayTagScalarPropertyContainer::InternalRemovePropertyMultiplier(const FFloatScalarModiferHandle& Handle)
{
	for (int i = 0;i < ModiferHandles.Num();++i)
	{
		if(ModiferHandles[i] == Handle)
		{
			ModiferHandles.RemoveAt(i);
			return true;
		}
	}
	return false;
}

void FGameplayTagScalarPropertyContainer::InternalRemoveAllMultiplier(const FGameplayTag& Tag)
{
	for (int i = 0; i<ModiferHandles.Num(); ++i)
	{
		if(ModiferHandles[i].Tag == Tag)
		{
			ModiferHandles.RemoveAt(i);
		}
	}
}

void FGameplayTagScalarPropertyContainer::PreReplicatedRemove(const TArrayView<int32> RemovedIndices, int32 FinalSize)
{
	for (int32 Index : RemovedIndices)
	{
		const FGameplayTag Tag = Properties[Index].Tag;
		TagToCountMap.Remove(Tag);
	}
}

void FGameplayTagScalarPropertyContainer::PostReplicatedAdd(const TArrayView<int32> AddedIndices, int32 FinalSize)
{
	for (int32 Index : AddedIndices)
	{
		const FGameplayTagScalarProperty& Property = Properties[Index];
		TagToCountMap.Add(Property.Tag, Property.FloatScalar);
	}
}

void FGameplayTagScalarPropertyContainer::PostReplicatedChange(const TArrayView<int32> ChangedIndices, int32 FinalSize)
{
	for (int32 Index : ChangedIndices)
	{
		const FGameplayTagScalarProperty& Property = Properties[Index];
		TagToCountMap[Property.Tag] = Property.FloatScalar;
	}
}

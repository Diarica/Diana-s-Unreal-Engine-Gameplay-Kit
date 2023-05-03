// Fill out your copyright notice in the Description page of Project Settings.


#include "TagProp.h"

#include "GameplayTagContainer.h"
//////////////////////////////////////////////////////////////////////
// FGameplayTagProperty

FString FGameplayTagProperty::GetDebugString() const
{
	return FString::Printf(TEXT("%sx%d"), *Tag.ToString(), PropertyCount);
}

//////////////////////////////////////////////////////////////////////
// FGameplayTagPropertyContainer

void FGameplayTagPropertyContainer::AddProperty(FGameplayTag Tag, int32 PropertyCount, int32 MaxCount)
{
	if (!Tag.IsValid())
	{
		FFrame::KismetExecutionMessage(TEXT("An invalid tag was passed to AddProperty"), ELogVerbosity::Warning);
		return;
	}

	if (PropertyCount <= MaxCount)
	{
		for (FGameplayTagProperty& Property : Propertys)
		{
			if (Property.Tag == Tag)
			{
				return;
			}
		}

		FGameplayTagProperty& NewProperty = Propertys.Emplace_GetRef(Tag, PropertyCount, MaxCount);
		MarkItemDirty(NewProperty);
		TagToCountMap.Add(Tag, PropertyCount);
	}
}

void FGameplayTagPropertyContainer::AddPropertyValue(FGameplayTag Tag, int32 PropertyCount)
{
	if(PropertyCount > 0)
	{
		for (FGameplayTagProperty& Property : Propertys)
		{
			if(Property.Tag == Tag)
			{
				const int32 NewCount = Property.PropertyCount + PropertyCount;
				Property.PropertyCount = NewCount;
				TagToCountMap[Tag] = NewCount;
				MarkItemDirty(Property);
				return;
			}
		}
	}
	
}



void FGameplayTagPropertyContainer::ReducePropertyValue(FGameplayTag Tag, int32 PropertyCount)
{
	if (!Tag.IsValid())
	{
		FFrame::KismetExecutionMessage(TEXT("An invalid tag was passed to RemoveProperty"), ELogVerbosity::Warning);
		return;
	}

	if (PropertyCount > 0)
	{
		for (auto It = Propertys.CreateIterator(); It; ++It)
		{
			FGameplayTagProperty& Property = *It;
			if (Property.Tag == Tag)
			{
				const int32 NewCount = Property.PropertyCount - PropertyCount;
				Property.PropertyCount = NewCount;
				TagToCountMap[Tag] = NewCount;
				MarkItemDirty(Property);
				
				return;
			}
		}
	}
	
}

void FGameplayTagPropertyContainer::ModifyMaxPropertyValue(FGameplayTag Tag, int32 MaxValue)
{
	if(!Tag.IsValid())
	{
		return;
	}
	
	if(MaxValue > 0)
	{
		for (auto It = Propertys.CreateIterator(); It; ++It)
		{
			FGameplayTagProperty& Property = *It;

			if(Property.Tag == Tag)
			{
				if(Property.MaxCount == MaxValue)
				{
					return;
				}

				

				Property.MaxCount = MaxValue;
				
				if(Property.PropertyCount >= MaxValue)
				{
					Property.PropertyCount = MaxValue;
				}

				

				TagToCountMap[Tag] = Property.PropertyCount;
				MarkItemDirty(Property);
				return;

				
			}
			
		}
	}
}

void FGameplayTagPropertyContainer::RemoveProperty(FGameplayTag Tag)
{
	if (!Tag.IsValid())
	{
		FFrame::KismetExecutionMessage(TEXT("An invalid tag was passed to RemoveProperty"), ELogVerbosity::Warning);
		return;
	}
	
	
		for (auto It = Propertys.CreateIterator(); It; ++It)
		{
			FGameplayTagProperty& Property = *It;
			if (Property.Tag == Tag)
			{
				It.RemoveCurrent();
				TagToCountMap.Remove(Tag);
				MarkArrayDirty();
				return;
			}
		}
	
}

void FGameplayTagPropertyContainer::PreReplicatedRemove(const TArrayView<int32> RemovedIndices, int32 FinalSize)
{
	for (int32 Index : RemovedIndices)
	{
		const FGameplayTag Tag = Propertys[Index].Tag;
		TagToCountMap.Remove(Tag);
	}
}

void FGameplayTagPropertyContainer::PostReplicatedAdd(const TArrayView<int32> AddedIndices, int32 FinalSize)
{
	for (int32 Index : AddedIndices)
	{
		const FGameplayTagProperty& Property = Propertys[Index];
		TagToCountMap.Add(Property.Tag, Property.PropertyCount);
	}
}

void FGameplayTagPropertyContainer::PostReplicatedChange(const TArrayView<int32> ChangedIndices, int32 FinalSize)
{
	for (int32 Index : ChangedIndices)
	{
		const FGameplayTagProperty& Property = Propertys[Index];
		TagToCountMap[Property.Tag] = Property.PropertyCount;
	}
}


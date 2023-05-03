// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "TagProp.generated.h"

/**
 * 
 */

struct FGameplayTagPropertyContainer;
struct FNetDeltaSerializeInfo;

/**
 * Represents one Property of a gameplay tag (tag + count)
 */
USTRUCT(BlueprintType)
struct FGameplayTagProperty : public FFastArraySerializerItem
{
	GENERATED_BODY()

	FGameplayTagProperty(): MaxCount(0)
	{
	}

	FGameplayTagProperty(FGameplayTag InTag, int32 InPropertyCount,int32 Max)
		: Tag(InTag)
		, PropertyCount(InPropertyCount),MaxCount(Max)
	{
	}

	FString GetDebugString() const;

private:
	friend FGameplayTagPropertyContainer;

	UPROPERTY()
	FGameplayTag Tag;

	UPROPERTY()
	int32 PropertyCount = 0;

	UPROPERTY()
	int32 MaxCount = 0;
};

/** Container of gameplay tag Propertys */
USTRUCT(BlueprintType)
struct FGameplayTagPropertyContainer : public FFastArraySerializer
{
	GENERATED_BODY()

	FGameplayTagPropertyContainer()
	//	: Owner(nullptr)
	{
	}

public:
	// Adds a specified number of Propertys to the tag (does nothing if PropertyCount is below 1)
	void AddProperty(FGameplayTag Tag, int32 PropertyCount, int32 MaxCount);

	void AddPropertyValue(FGameplayTag Tag, int32 PropertyCount);

	// Removes a specified number of Propertys from the tag (does nothing if PropertyCount is below 1)
	void RemoveProperty(FGameplayTag Tag); 

	void ReducePropertyValue(FGameplayTag Tag, int32 PropertyCount);

	void ModifyMaxPropertyValue(FGameplayTag Tag,int32 MaxValue);

	// Returns the Property count of the specified tag (or 0 if the tag is not present)
	int32 GetPropertyCount(FGameplayTag Tag) const
	{
		return TagToCountMap.FindRef(Tag);
	}

	// Returns true if there is at least one Property of the specified tag
	bool ContainsTag(FGameplayTag Tag) const
	{
		return TagToCountMap.Contains(Tag);
	}

	//~FFastArraySerializer contract
	void PreReplicatedRemove(const TArrayView<int32> RemovedIndices, int32 FinalSize);
	void PostReplicatedAdd(const TArrayView<int32> AddedIndices, int32 FinalSize);
	void PostReplicatedChange(const TArrayView<int32> ChangedIndices, int32 FinalSize);
	//~End of FFastArraySerializer contract

	bool NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParms)
	{
		return FFastArraySerializer::FastArrayDeltaSerialize<FGameplayTagProperty, FGameplayTagPropertyContainer>(Propertys, DeltaParms, *this);
	}

private:
	// Replicated list of gameplay tag Propertys
	UPROPERTY()
	TArray<FGameplayTagProperty> Propertys;
	
	// Accelerated list of tag Propertys for queries
	TMap<FGameplayTag, int32> TagToCountMap;
};

template<>
struct TStructOpsTypeTraits<FGameplayTagPropertyContainer> : public TStructOpsTypeTraitsBase2<FGameplayTagPropertyContainer>
{
	enum
	{
		WithNetDeltaSerializer = true,
	};
};


UCLASS()
class FLATLINE_API UTagProp : public UObject
{
	GENERATED_BODY()
};

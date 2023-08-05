// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Net/Serialization/FastArraySerializer.h"
#include "UObject/Object.h"
#include "TagScalarProp.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FFloatScalarModiferHandle
{
	GENERATED_BODY()

	FFloatScalarModiferHandle(FGameplayTag InTag = FGameplayTag::EmptyTag,float InMultiplier = 1.00)
	{
		Tag = InTag;
		Multiplier = InMultiplier;
	}

	FGameplayTag Tag;
	
	float Multiplier;

	bool operator == (const FFloatScalarModiferHandle& Handle) const
	{
		return Handle.Multiplier == Multiplier && Handle.Tag == Tag;
	}
};

USTRUCT(BlueprintType)
struct FFloatScalar
{
	GENERATED_BODY()
	
	FFloatScalar()
	{
		
	}

	FFloatScalar(const float Baseval)
	{
		SetBaseValue(Baseval);
		UpdateValue();
	}

	
	FORCEINLINE float Get() const
	{
		return ResultValue;
	}
	FORCEINLINE float GetMultiplier() const
	{
		return Multiplier;
	}
	FORCEINLINE float GetBaseValue() const
	{
		return BaseValue;
	}

	FORCEINLINE void SetMultiplier(float multiplier)
	{
		Multiplier = multiplier;
		UpdateValue();
	}
	
	FORCEINLINE void SetBaseValue(float val)
	{
		BaseValue = val;
		UpdateValue();
		
	}
private:
	UPROPERTY()
	float ResultValue = 0;
	
	UPROPERTY(EditDefaultsOnly)
	float BaseValue = 0;

	UPROPERTY()
	float Multiplier = 1.0;


public:
	FORCEINLINE void UpdateValue()
	{
		ResultValue = BaseValue * Multiplier;
	}
	
	
}


;
struct FGameplayTagScalarPropertyContainer;
struct FNetDeltaSerializeInfo;

/**
 * Represents one Property of a gameplay tag (tag + count)
 */
USTRUCT(BlueprintType)
struct FGameplayTagScalarProperty : public FFastArraySerializerItem
{
	GENERATED_BODY()

	FGameplayTagScalarProperty()
	{
		
	}


	FGameplayTagScalarProperty(FGameplayTag InTag, float BaseValue) : FloatScalar(BaseValue)
	{
		Tag = InTag;
		
	}

	FString GetDebugString() const;

private:
	friend FGameplayTagScalarPropertyContainer;

	UPROPERTY()
	FGameplayTag Tag;

	UPROPERTY()
	FFloatScalar FloatScalar;

	
};

/** Container of gameplay tag Properties */
USTRUCT(BlueprintType)
struct FGameplayTagScalarPropertyContainer : public FFastArraySerializer
{
	GENERATED_BODY()

	FGameplayTagScalarPropertyContainer()
	//	: Owner(nullptr)
	{
	}

public:
	
	void AddProperty(FGameplayTag Tag, float BaseValue);
	void RemoveProperty(FGameplayTag Tag);

	FFloatScalarModiferHandle AddPropertyMultiplier(FGameplayTag Tag, float Multiplier);
	bool RemovePropertyMultiplier(FFloatScalarModiferHandle& Handle);
	
	


	

	// Returns the Property count of the specified tag (or 0 if the tag is not present)
	FORCEINLINE float GetPropertyValue(const FGameplayTag& Tag) const
	{
		return TagToCountMap[Tag].Get();
	}

	// Returns true if there is at least one Property of the specified tag
	bool ContainsTag(const FGameplayTag Tag) const
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
		return FFastArraySerializer::FastArrayDeltaSerialize<FGameplayTagScalarProperty, FGameplayTagScalarPropertyContainer>(Properties, DeltaParms, *this);
	}

private:
	FFloatScalarModiferHandle InternalAddPropertyMultiplier(const FGameplayTag& Tag, float Multiplier);
	bool InternalRemovePropertyMultiplier(const FFloatScalarModiferHandle& Handle);
	void InternalRemoveAllMultiplier(const FGameplayTag& Tag);
private:
	// Replicated list of gameplay tag Properties
	UPROPERTY()
	TArray<FGameplayTagScalarProperty> Properties;
	
	// Accelerated list of tag Properties for queries
	TMap<FGameplayTag, FFloatScalar> TagToCountMap;

	// List of tag properties multipliers,SERVER ONLY 
	TArray<FFloatScalarModiferHandle> ModiferHandles;

	
};

template<>
struct TStructOpsTypeTraits<FGameplayTagScalarPropertyContainer> : public TStructOpsTypeTraitsBase2<FGameplayTagScalarPropertyContainer>
{
	enum
	{
		WithNetDeltaSerializer = true,
	};
};


UCLASS()
class FLATLINE_API UTagScalarProp : public UObject
{
	GENERATED_BODY()
};

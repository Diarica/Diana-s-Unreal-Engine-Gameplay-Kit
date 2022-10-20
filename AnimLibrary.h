// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayLib.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AnimLibrary.generated.h"

/**
 * 
 */
UCLASS()
class FLATLINE_API UAnimLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	static void PlayAnimation(USkeletalMeshComponent * Mesh,UAnimationAsset*Anim,bool bLoop)
	{
		if(Mesh && Anim)
		{
			Mesh->PlayAnimation(Anim,bLoop);
		}
	}


	static void PlayAnimation_Random(USkeletalMeshComponent * Mesh,TArray<UAnimationAsset*> &Anims,bool bLoop)
	{
		if(Mesh && !Anims.IsEmpty())
		{
			int result = UGameplayLib::GetRandomIndexOfTArray(Anims);
			if(Anims.IsValidIndex(result) && !Anims.IsEmpty())
			{
				Mesh->PlayAnimation(Anims[result],bLoop);
			}
		}
	}

	static void PlayMontage(UAnimInstance * Instance,UAnimMontage* MontageToPlay, float InPlayRate = 1.f, EMontagePlayReturnType ReturnValueType = EMontagePlayReturnType::MontageLength, float InTimeToStartMontageAt=0.f, bool bStopAllMontages = true,FName SectionName ="")
	{
		if(Instance && MontageToPlay)
		{
			Instance->Montage_Play(MontageToPlay,InPlayRate,ReturnValueType,InTimeToStartMontageAt,bStopAllMontages);
			if(SectionName.IsNone())
			{
				Instance->Montage_JumpToSection(SectionName,MontageToPlay);
			}
		}
	}

	static void PlayMontage_Random(UAnimInstance * Instance,TArray<UAnimMontage*> &Montages, float InPlayRate = 1.f, EMontagePlayReturnType ReturnValueType = EMontagePlayReturnType::MontageLength, float InTimeToStartMontageAt=0.f, bool bStopAllMontages = true)
	{
		int result = UGameplayLib::GetRandomIndexOfTArray(Montages);
		if(Montages.IsValidIndex(result) && !Montages.IsEmpty())
		{
			PlayMontage(Instance,Montages[result],InPlayRate,ReturnValueType,InTimeToStartMontageAt,bStopAllMontages);
		}
		
	}

	
	
};

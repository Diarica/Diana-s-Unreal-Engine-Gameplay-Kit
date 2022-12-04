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
	static void PlayAnimation(USkeletalMeshComponent * Mesh,UAnimationAsset*Anim,bool bLoop,float PlayRate = 1)
	{
		if(Mesh && Anim)
		{
			Mesh->GlobalAnimRateScale = PlayRate;
			Mesh->PlayAnimation(Anim,bLoop);
		}
	}


	static void PlayAnimation_Random(USkeletalMeshComponent * Mesh,TArray<UAnimationAsset*> &Anims,bool bLoop,float PlayRate = 1)
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

	static void PlayMontage(UAnimInstance * Instance,UAnimMontage* MontageToPlay, bool bStopAllMontages = true, float RateScale = 1.f, EMontagePlayReturnType ReturnValueType = EMontagePlayReturnType::MontageLength, float InTimeToStartMontageAt=0.f,FName SectionName ="")
	{
		if(Instance && MontageToPlay)
		{
			Instance->Montage_Play(MontageToPlay,RateScale,ReturnValueType,InTimeToStartMontageAt,bStopAllMontages);
			
			if(SectionName.IsNone())
			{
				return;
			}
			Instance->Montage_JumpToSection(SectionName,MontageToPlay);
		}
	}
	

	

	static float PlayMontage_ReturnVal(UAnimInstance * Instance,UAnimMontage* MontageToPlay, bool bStopAllMontages = true, float RateScale = 1.f, EMontagePlayReturnType ReturnValueType = EMontagePlayReturnType::MontageLength, float InTimeToStartMontageAt=0.f,FName SectionName ="")
	{
		if(Instance && MontageToPlay)
		{
			const float Duration = Instance->Montage_Play(MontageToPlay,RateScale,ReturnValueType,InTimeToStartMontageAt,bStopAllMontages);
			//Instance->OnPlayMontageNotifyBegin.AddDynamic()
			
			if(SectionName.IsNone())
			{
				
			}
			Instance->Montage_JumpToSection(SectionName,MontageToPlay);
			return Duration;
		}
		return 0;
		
	}

	static void PlayMontage_Random(UAnimInstance * Instance,TArray<UAnimMontage*> &Montages, float RateScale = 1.f, EMontagePlayReturnType ReturnValueType = EMontagePlayReturnType::MontageLength, float InTimeToStartMontageAt=0.f, bool bStopAllMontages = true)
	{
		int result = UGameplayLib::GetRandomIndexOfTArray(Montages);
		if(Montages.IsValidIndex(result) && !Montages.IsEmpty())
		{
			PlayMontage(Instance,Montages[result],bStopAllMontages,RateScale);
		}
		
	}

	
	
};

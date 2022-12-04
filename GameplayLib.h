// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameplayLib.generated.h"

/**
 * 
 */
UCLASS()
class FLATLINE_API UGameplayLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	static void AttachToMesh(USkeletalMeshComponent * ParentMeshToAttach,USkeletalMeshComponent * ChildMeshToAttach,FName &SocketName,bool bSimulateBody = false)
	{
		if(ParentMeshToAttach != nullptr && ChildMeshToAttach != nullptr)
		{
			ChildMeshToAttach->K2_AttachToComponent(ParentMeshToAttach, SocketName, EAttachmentRule::SnapToTarget,
			                                EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget,
			                                bSimulateBody);
		}
	}

	static void AttachToMesh(USkeletalMeshComponent * ParentMeshToAttach,UStaticMeshComponent * ChildStaticMeshToAttach,FName &SocketName,bool bSimulateBody = false)
	{
		if(ParentMeshToAttach != nullptr && ChildStaticMeshToAttach != nullptr)
		{
			ChildStaticMeshToAttach->K2_AttachToComponent(ParentMeshToAttach, SocketName, EAttachmentRule::SnapToTarget,
											EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget,
											bSimulateBody);
		}
	}

	static void AttachActorToMesh(USkeletalMeshComponent * ParentMesh,AActor * ActorToAttached,FName &SocketName)
	{
		if(ParentMesh ==nullptr || ActorToAttached == nullptr)
		{
			return;
			
		}

		ActorToAttached->AttachToComponent(ParentMesh,FAttachmentTransformRules::SnapToTargetIncludingScale,SocketName);
	}

	static void AttachActorToMesh(UStaticMeshComponent * ParentMesh,AActor * ActorToAttached,FName &SocketName)
	{
		if(ParentMesh == nullptr || ActorToAttached == nullptr)
		{

			return;
			
		}
		ActorToAttached->AttachToComponent(ParentMesh,FAttachmentTransformRules::SnapToTargetIncludingScale,SocketName);
	}
	

	template<typename T>
	static int GetRandomIndexOfTArray(TArray<T> &Array)
	{
		int RandResult = FMath::RandRange(0,Array.Num());
			if(Array.IsValidIndex(RandResult))
			{
				return RandResult;
			}

		return 0;
	}

	

	static void PlayParticleAttached(UParticleSystem * ParticleToSpawn,USceneComponent * ObjectToAttach,FName& AttachPointName, FVector Location = FVector(ForceInit), FRotator Rotation = FRotator::ZeroRotator, FVector Scale = FVector(1.f), EAttachLocation::Type LocationType = EAttachLocation::KeepRelativeOffset,bool bAutoActivate=true,bool bUsePooling = true)
	{
		if(ParticleToSpawn == nullptr || ObjectToAttach == nullptr)
			return;
		if(bUsePooling)
		{
			UGameplayStatics::SpawnEmitterAttached(ParticleToSpawn,ObjectToAttach,AttachPointName,Location,Rotation,Scale,EAttachLocation::SnapToTargetIncludingScale,true,EPSCPoolMethod::AutoRelease,bAutoActivate);
		}
		else
		{
			UGameplayStatics::SpawnEmitterAttached(ParticleToSpawn,ObjectToAttach,AttachPointName,Location,Rotation,Scale,EAttachLocation::SnapToTargetIncludingScale,true,EPSCPoolMethod::None,bAutoActivate);
		}
	}

	static void PlayParticleAttached(TArray<UParticleSystem*> &Particles,USceneComponent * ObjectToAttach,FName& AttachPointName, FVector Location = FVector(ForceInit), FRotator Rotation = FRotator::ZeroRotator, FVector Scale = FVector(1.f), EAttachLocation::Type LocationType = EAttachLocation::KeepRelativeOffset,bool bAutoActivate=true,bool bUsePooling = true)
	{
		if(ObjectToAttach == nullptr)
			return;

		int result = UGameplayLib::GetRandomIndexOfTArray(Particles);
		if(!Particles.IsValidIndex(result))
		{
			return;
		}
		if(bUsePooling)
		{
			UGameplayStatics::SpawnEmitterAttached(Particles[result],ObjectToAttach,AttachPointName,Location,Rotation,Scale,EAttachLocation::SnapToTargetIncludingScale,true,EPSCPoolMethod::AutoRelease,bAutoActivate);
		}
		else
		{
			UGameplayStatics::SpawnEmitterAttached(Particles[result],ObjectToAttach,AttachPointName,Location,Rotation,Scale,EAttachLocation::SnapToTargetIncludingScale,true,EPSCPoolMethod::None,bAutoActivate);
		}
	}

	static void PlayParticleAtLocation(const UObject* WorldContextObject, UParticleSystem* EmitterTemplate, bool bPooling,FVector Location, FRotator Rotation = FRotator::ZeroRotator, FVector Scale = FVector(1.f), bool bAutoDestroy = false, bool bAutoActivateSystem = true)
	{
		if(WorldContextObject == nullptr || EmitterTemplate == nullptr)
			return;

		if(bPooling)
		{
			UGameplayStatics::SpawnEmitterAtLocation(WorldContextObject,EmitterTemplate,Location,Rotation,Scale,bAutoDestroy,EPSCPoolMethod::AutoRelease,bAutoActivateSystem);
		}
		else
		{
			UGameplayStatics::SpawnEmitterAtLocation(WorldContextObject,EmitterTemplate,Location,Rotation,Scale,bAutoDestroy,EPSCPoolMethod::None,bAutoActivateSystem);
			
		}
	}


	

	
	

	
};

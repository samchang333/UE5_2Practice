// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Animation/AnimNotifies/AnimNotify.h"
#include "Chaos/ChaosEngineInterface.h"
#include "GameplayTagContainer.h"
#include "Engine/EngineTypes.h"
#include "AnimNotify_PracticeContextEffects.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct UE5PRACTICE_API FPracticeContextEffectAnimNotifyVFXSettings
{
	GENERATED_BODY()

	// Scale to spawn the particle system at
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FX)
	FVector Scale = FVector(1.0f, 1.0f, 1.0f);

};

/**
 *
 */
USTRUCT(BlueprintType)
struct UE5PRACTICE_API FPracticeContextEffectAnimNotifyAudioSettings
{
	GENERATED_BODY()

	// Volume Multiplier
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sound)
	float VolumeMultiplier = 1.0f;

	// Pitch Multiplier
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sound)
	float PitchMultiplier = 1.0f;
};


/**
 *
 */
USTRUCT(BlueprintType)
struct UE5PRACTICE_API FPracticeContextEffectAnimNotifyTraceSettings
{
	GENERATED_BODY()

	// Trace Channel
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Trace)
	TEnumAsByte<ECollisionChannel> TraceChannel = ECollisionChannel::ECC_Visibility;

	// Vector offset from Effect Location
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Trace)
	FVector EndTraceLocationOffset = FVector::ZeroVector;

	// Ignore this Actor when getting trace result
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Trace)
	bool bIgnoreActor = true;
};

/**
 *
 */
USTRUCT(BlueprintType)
struct UE5PRACTICE_API FPracticeContextEffectAnimNotifyPreviewSettings
{
	GENERATED_BODY()

	// If true, will attempt to match selected Surface Type to Context Tag via Project Settings
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Preview)
	bool bPreviewPhysicalSurfaceAsContext = true;

	// Surface Type
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Preview, meta=(EditCondition="bPreviewPhysicalSurfaceAsContext"))
	TEnumAsByte<EPhysicalSurface> PreviewPhysicalSurface = EPhysicalSurface::SurfaceType_Default;

	// Preview Library
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Preview, meta = (AllowedClasses = "/Script/PracticeGame.PracticeContextEffectsLibrary"))
	FSoftObjectPath PreviewContextEffectsLibrary;

	// Preview Context
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Preview)
	FGameplayTagContainer PreviewContexts;
};


/**
 * 
 */
UCLASS(const, hidecategories=Object, CollapseCategories, Config = Game, meta=(DisplayName="Play Context Effects"))
class UE5PRACTICE_API UAnimNotify_PracticeContextEffects : public UAnimNotify
{
	GENERATED_BODY()

public:
	UAnimNotify_PracticeContextEffects();

	// Begin UObject interface
	virtual void PostLoad() override;
#if WITH_EDITOR
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
	// End UObject interface

	// Begin UAnimNotify interface
	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
#if WITH_EDITOR
	virtual void ValidateAssociatedAssets() override;
#endif
	// End UAnimNotify interface

#if WITH_EDITOR
	UFUNCTION(BlueprintCallable)
	void SetParameters(FGameplayTag EffectIn, FVector LocationOffsetIn, FRotator RotationOffsetIn, 
		FPracticeContextEffectAnimNotifyVFXSettings VFXPropertiesIn, FPracticeContextEffectAnimNotifyAudioSettings AudioPropertiesIn,
		bool bAttachedIn, FName SocketNameIn, bool bPerformTraceIn, FPracticeContextEffectAnimNotifyTraceSettings TracePropertiesIn);
#endif


	// Effect to Play
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimNotify", meta = (DisplayName = "Effect", ExposeOnSpawn = true))
	FGameplayTag Effect;

	// Location offset from the socket
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimNotify", meta = (ExposeOnSpawn = true))
	FVector LocationOffset = FVector::ZeroVector;

	// Rotation offset from socket
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimNotify", meta = (ExposeOnSpawn = true))
	FRotator RotationOffset = FRotator::ZeroRotator;

	// Scale to spawn the particle system at
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimNotify", meta = (ExposeOnSpawn = true))
	FPracticeContextEffectAnimNotifyVFXSettings VFXProperties;

	// Scale to spawn the particle system at
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimNotify", meta = (ExposeOnSpawn = true))
	FPracticeContextEffectAnimNotifyAudioSettings AudioProperties;

	// Should attach to the bone/socket
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttachmentProperties", meta = (ExposeOnSpawn = true))
	uint32 bAttached : 1; 	//~ Does not follow coding standard due to redirection from BP

	// SocketName to attach to
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttachmentProperties", meta = (ExposeOnSpawn = true, EditCondition = "bAttached"))
	FName SocketName;

	// Will perform a trace, required for SurfaceType to Context Conversion
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimNotify", meta = (ExposeOnSpawn = true))
	uint32 bPerformTrace : 1; 	

	// Scale to spawn the particle system at
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimNotify", meta = (ExposeOnSpawn = true, EditCondition = "bPerformTrace"))
	FPracticeContextEffectAnimNotifyTraceSettings TraceProperties;

#if WITH_EDITORONLY_DATA
	UPROPERTY(Config, EditAnywhere, Category = "PreviewProperties")
	uint32 bPreviewInEditor : 1;

	UPROPERTY(EditAnywhere, Category = "PreviewProperties", meta = (EditCondition = "bPreviewInEditor"))
	FPracticeContextEffectAnimNotifyPreviewSettings PreviewProperties;
#endif


};

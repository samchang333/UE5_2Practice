// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Camera/PlayerCameraManager.h"

#include "PracticePlayerCameraManager.generated.h"

class FDebugDisplayInfo;
class UCanvas;
class UObject;


#define PRACTICE_CAMERA_DEFAULT_FOV			(80.0f)
#define PRACTICE_CAMERA_DEFAULT_PITCH_MIN	(-89.0f)
#define PRACTICE_CAMERA_DEFAULT_PITCH_MAX	(89.0f)

class UPracticeUICameraManagerComponent;

/**
 * APracticePlayerCameraManager
 *
 *	The base player camera manager class used by this project.
 */
UCLASS(notplaceable, MinimalAPI)
class APracticePlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()

public:

	APracticePlayerCameraManager(const FObjectInitializer& ObjectInitializer);

	UPracticeUICameraManagerComponent* GetUICameraComponent() const;

protected:

	virtual void UpdateViewTarget(FTViewTarget& OutVT, float DeltaTime) override;

	virtual void DisplayDebug(UCanvas* Canvas, const FDebugDisplayInfo& DebugDisplay, float& YL, float& YPos) override;

private:
	/** The UI Camera Component, controls the camera when UI is doing something important that gameplay doesn't get priority over. */
	UPROPERTY(Transient)
	TObjectPtr<UPracticeUICameraManagerComponent> UICamera;
};

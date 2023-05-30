// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Messaging/CommonMessagingSubsystem.h"
#include "Templates/SubclassOf.h"
#include "UObject/SoftObjectPtr.h"

#include "PracticeUIMessaging.generated.h"

class FSubsystemCollectionBase;
class UCommonGameDialog;
class UCommonGameDialogDescriptor;
class UObject;

/**
 * 
 */
UCLASS()
class UPracticeUIMessaging : public UCommonMessagingSubsystem
{
	GENERATED_BODY()

public:
	UPracticeUIMessaging() { }

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void ShowConfirmation(UCommonGameDialogDescriptor* DialogDescriptor, FCommonMessagingResultDelegate ResultCallback = FCommonMessagingResultDelegate()) override;
	virtual void ShowError(UCommonGameDialogDescriptor* DialogDescriptor, FCommonMessagingResultDelegate ResultCallback = FCommonMessagingResultDelegate()) override;

private:
	UPROPERTY()
	TSubclassOf<UCommonGameDialog> ConfirmationDialogClassPtr;

	UPROPERTY()
	TSubclassOf<UCommonGameDialog> ErrorDialogClassPtr;

	UPROPERTY(config)
	TSoftClassPtr<UCommonGameDialog> ConfirmationDialogClass;

	UPROPERTY(config)
	TSoftClassPtr<UCommonGameDialog> ErrorDialogClass;
};

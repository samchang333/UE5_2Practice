// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Engine/DeveloperSettings.h"
#include "PracticeTextHotfixConfig.generated.h"

struct FPolyglotTextData;
struct FPropertyChangedEvent;

/**
 * This class allows hotfixing individual FText values anywhere
 */

UCLASS(config=Game, defaultconfig)
class UPracticeTextHotfixConfig : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPracticeTextHotfixConfig(const FObjectInitializer& ObjectInitializer);

	// UObject interface
	virtual void PostInitProperties() override;
	virtual void PostReloadConfig(FProperty* PropertyThatWasLoaded) override;
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
	// End of UObject interface

private:
	void ApplyTextReplacements() const;

private:
	// The list of FText values to hotfix
	UPROPERTY(Config, EditAnywhere)
	TArray<FPolyglotTextData> TextReplacements;
};

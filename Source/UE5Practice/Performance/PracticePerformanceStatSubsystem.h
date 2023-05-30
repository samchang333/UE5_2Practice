// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "ChartCreation.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "PracticePerformanceStatSubsystem.generated.h"

enum class EPracticeDisplayablePerformanceStat : uint8;

class FSubsystemCollectionBase;
class UPracticePerformanceStatSubsystem;
class UObject;
struct FFrame;

//////////////////////////////////////////////////////////////////////

// Observer which caches the stats for the previous frame
struct FPracticePerformanceStatCache : public IPerformanceDataConsumer
{
public:
	FPracticePerformanceStatCache(UPracticePerformanceStatSubsystem* InSubsystem)
		: MySubsystem(InSubsystem)
	{
	}

	//~IPerformanceDataConsumer interface
	virtual void StartCharting() override;
	virtual void ProcessFrame(const FFrameData& FrameData) override;
	virtual void StopCharting() override;
	//~End of IPerformanceDataConsumer interface

	double GetCachedStat(EPracticeDisplayablePerformanceStat Stat) const;

protected:
	IPerformanceDataConsumer::FFrameData CachedData;
	UPracticePerformanceStatSubsystem* MySubsystem;

	float CachedServerFPS = 0.0f;
	float CachedPingMS = 0.0f;
	float CachedPacketLossIncomingPercent = 0.0f;
	float CachedPacketLossOutgoingPercent = 0.0f;
	float CachedPacketRateIncoming = 0.0f;
	float CachedPacketRateOutgoing = 0.0f;
	float CachedPacketSizeIncoming = 0.0f;
	float CachedPacketSizeOutgoing = 0.0f;
};

//////////////////////////////////////////////////////////////////////

// Subsystem to allow access to performance stats for display purposes
UCLASS(BlueprintType)
class UPracticePerformanceStatSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	double GetCachedStat(EPracticeDisplayablePerformanceStat Stat) const;

	//~USubsystem interface
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	//~End of USubsystem interface

protected:
	TSharedPtr<FPracticePerformanceStatCache> Tracker;
};

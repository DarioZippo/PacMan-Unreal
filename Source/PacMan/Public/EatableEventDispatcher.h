// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "EatableEventDispatcher.generated.h"

UENUM(BlueprintType)
enum class EEatEvent : uint8 {  
	Dot UMETA(DisplayName = "Dot"),
	Pellet UMETA(DisplayName = "Pellet"),
	Ghost UMETA(DisplayName = "Ghost")
};

DECLARE_MULTICAST_DELEGATE(FEatEvent);
DECLARE_MULTICAST_DELEGATE(FEatPelletEvent);
DECLARE_MULTICAST_DELEGATE(FEatGhostEvent);

UCLASS()
class PACMAN_API UEatableEventDispatcher : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	FEatEvent OnEatEvent;
	FEatPelletEvent OnEatPelletEvent;
	FEatGhostEvent OnEatGhostEvent;

public:
	void DispatchEatEvent(const EEatEvent& EatEvent);
};

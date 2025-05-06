// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EGhostState : uint8 {  
	Chase UMETA(DisplayName = "Chase"),
	Scatter UMETA(DisplayName = "Scatter"),
	Frightened UMETA(DisplayName = "Frightened"),
	Eaten UMETA(DisplayName = "Eaten")
};
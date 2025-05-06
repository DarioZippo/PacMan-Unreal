// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Teleportable.generated.h"

UINTERFACE(MinimalAPI, BlueprintType)
class UTeleportable : public UInterface{
	GENERATED_BODY()
};

/**
 * 
 */
class PACMAN_API ITeleportable
{
	GENERATED_BODY()

public:
	virtual void SetIsTeleporting(bool NewIsTeleporting) = 0;
	virtual bool GetIsTeleporting() = 0;
};
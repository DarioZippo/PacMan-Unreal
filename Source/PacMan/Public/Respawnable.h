// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Respawnable.generated.h"

UINTERFACE(MinimalAPI, BlueprintType)
class URespawnable : public UInterface{
	GENERATED_BODY()
};

class PACMAN_API IRespawnable
{
	GENERATED_BODY()

public:
	virtual void Respawn() = 0;
};

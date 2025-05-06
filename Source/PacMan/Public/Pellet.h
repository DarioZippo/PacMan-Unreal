// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Dot.h"
#include "Pellet.generated.h"

/**
 * 
 */
UCLASS()
class PACMAN_API APellet : public ADot
{
	GENERATED_BODY()

public:
	virtual void Eat() override;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Eatable.generated.h"

UINTERFACE(MinimalAPI, BlueprintType)
class UEatable : public UInterface{
	GENERATED_BODY()
};

/**
 * 
 */
class PACMAN_API IEatable
{
	GENERATED_BODY()

public:
	virtual void Eat() = 0;
	virtual bool GetIsEatable() = 0;
};

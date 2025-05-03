// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Eatable.generated.h"

// This class does not need to be modified.
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

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void Eat() = 0;
	virtual bool GetIsEatable() = 0;
};

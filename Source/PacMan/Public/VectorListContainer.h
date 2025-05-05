// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "VectorListContainer.generated.h"

/**
 * 
 */
UCLASS()
class PACMAN_API UVectorListContainer : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY()
	TArray<FVector2D> VectorArray;

public:
	UVectorListContainer();
};
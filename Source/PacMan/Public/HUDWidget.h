// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"

class UTextBlock;
class UImage;
/**
 * 
 */
UCLASS()
class PACMAN_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ScoreText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> LifesText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> LifesIcon;

protected:
	void NativeConstruct();

	UFUNCTION()
	void UpdateScore(int NewScore);
};
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PacManGameMode.generated.h"

class UHUDWidget;
class UScoreManager;

UCLASS()
class PACMAN_API APacManGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Managers")
	TObjectPtr<UScoreManager> ScoreManager;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	UHUDWidget* HUDWidget;

public:
	APacManGameMode();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
};
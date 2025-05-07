// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PacManGameMode.generated.h"

class ULifeManager;
class UHUDWidget;
class UScoreManager;

DECLARE_MULTICAST_DELEGATE(FResetGameEvent);

UCLASS()
class PACMAN_API APacManGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	static FResetGameEvent OnResetGameEvent;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Managers")
	TObjectPtr<UScoreManager> ScoreManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Managers")
	TObjectPtr<ULifeManager> LifeManager;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TObjectPtr<UHUDWidget> HUDWidget;

public:
	APacManGameMode();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
	void CheckLifes(int NewLifes);
	
	UFUNCTION(BlueprintCallable)
	void ResetGame();
};
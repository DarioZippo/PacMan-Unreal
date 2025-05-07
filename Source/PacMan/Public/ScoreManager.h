// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ScoreManager.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FScoreUpdateEvent, int);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PACMAN_API UScoreManager : public UActorComponent
{
	GENERATED_BODY()

public:
	static FScoreUpdateEvent OnScoreUpdateEvent;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score")
	int Score;
	
public:
	UScoreManager();
	
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UFUNCTION()
	void AddScore(int ScoreIncrement);
	
	UFUNCTION()
	void UpdateScore(int NewScore);
};

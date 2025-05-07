// Fill out your copyright notice in the Description page of Project Settings.


#include "PacManGameMode.h"

#include "HUDWidget.h"
#include "LifeManager.h"
#include "ScoreManager.h"
#include "Kismet/GameplayStatics.h"

FResetGameEvent APacManGameMode::OnResetGameEvent;

APacManGameMode::APacManGameMode(){
	PrimaryActorTick.bCanEverTick = true;

	ScoreManager = CreateDefaultSubobject<UScoreManager>(TEXT("ScoreManager"));
	AddOwnedComponent(ScoreManager);

	LifeManager = CreateDefaultSubobject<ULifeManager>(TEXT("LifeManager"));
	AddOwnedComponent(LifeManager);
}

void APacManGameMode::BeginPlay(){
	Super::BeginPlay();

	ULifeManager::OnLifesUpdateEvent.AddUObject(this, &APacManGameMode::CheckLifes);

	if(HUDWidget){
		HUDWidget->AddToViewport();
	}
}

void APacManGameMode::Tick(float DeltaSeconds){
	Super::Tick(DeltaSeconds);
}

void APacManGameMode::CheckLifes(int NewLifes){
	if (NewLifes < 1){
		ResetGame();
	}
}

void APacManGameMode::ResetGame(){
	//In case of GameInstance's updates
	OnResetGameEvent.Broadcast();

	FName CurrentLevelName = *GetWorld()->GetMapName();
	UGameplayStatics::OpenLevel(this, CurrentLevelName, true);
}
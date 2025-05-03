// Fill out your copyright notice in the Description page of Project Settings.


#include "PacManGameMode.h"

#include "HUDWidget.h"
#include "ScoreManager.h"

APacManGameMode::APacManGameMode(){
	PrimaryActorTick.bCanEverTick = true;

	ScoreManager = CreateDefaultSubobject<UScoreManager>(TEXT("ScoreManager"));
	AddOwnedComponent(ScoreManager);
}

void APacManGameMode::BeginPlay(){
	Super::BeginPlay();

	if(HUDWidget){
		HUDWidget->AddToViewport();
	}
}

void APacManGameMode::Tick(float DeltaSeconds){
	Super::Tick(DeltaSeconds);
}

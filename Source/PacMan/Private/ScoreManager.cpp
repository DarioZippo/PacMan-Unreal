// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreManager.h"

#include "EatableEventDispatcher.h"

FScoreUpdateEvent UScoreManager::OnScoreUpdateEvent;

UScoreManager::UScoreManager(){
	PrimaryComponentTick.bCanEverTick = true;
	
	Score = 0;
}

void UScoreManager::BeginPlay(){
	Super::BeginPlay();
	
	UEatableEventDispatcher* EatableEventDispatcher = GetWorld()->GetGameInstance()->GetSubsystem<UEatableEventDispatcher>();
	if (EatableEventDispatcher){
		EatableEventDispatcher->OnEatEvent.AddUObject(this, &UScoreManager::AddScore);
	}
}

void UScoreManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction){
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UScoreManager::UpdateScore(int NewScore){
	Score = NewScore;

	OnScoreUpdateEvent.Broadcast(Score);
}

void UScoreManager::AddScore(int ScoreIncrement){
	Score += ScoreIncrement;

	OnScoreUpdateEvent.Broadcast(Score);
}
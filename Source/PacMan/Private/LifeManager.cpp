// Fill out your copyright notice in the Description page of Project Settings.


#include "LifeManager.h"

#include "PacManCharacter.h"

FLifesUpdateEvent ULifeManager::OnLifesUpdateEvent;

ULifeManager::ULifeManager(){
	PrimaryComponentTick.bCanEverTick = true;
	
	Lifes = 3;
}

void ULifeManager::BeginPlay(){
	Super::BeginPlay();
	
	APacManCharacter::OnDeathEvent.AddUObject(this, &ULifeManager::LoseLife);
}

void ULifeManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction){
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void ULifeManager::UpdateLifes(int NewLifes){
	Lifes = NewLifes;

	OnLifesUpdateEvent.Broadcast(Lifes);
}

void ULifeManager::LoseLife(){
	Lifes--;

	OnLifesUpdateEvent.Broadcast(Lifes);
}
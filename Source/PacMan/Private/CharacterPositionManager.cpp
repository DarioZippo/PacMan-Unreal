// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterPositionManager.h"

#include "Respawnable.h"

ACharacterPositionManager* ACharacterPositionManager::Instance = nullptr;

ACharacterPositionManager::ACharacterPositionManager(){
	PrimaryActorTick.bCanEverTick = true;
}

void ACharacterPositionManager::BeginPlay(){
	Super::BeginPlay();

	if (Instance != nullptr){
		this->Destroy();
	}
	Instance = this;
}

void ACharacterPositionManager::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
}

FTransform ACharacterPositionManager::GetRespawnPosition(ESpawnableCharacter Character){
	return CharacterPositionsMap[Character]->GetTransform();
}
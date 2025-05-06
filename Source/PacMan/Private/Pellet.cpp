// Fill out your copyright notice in the Description page of Project Settings.


#include "Pellet.h"

#include "EatableEventDispatcher.h"

void APellet::Eat(){
	SetActorEnableCollision(false);
	SetActorHiddenInGame(true);
	
	UEatableEventDispatcher* EatableEventDispatcher = GetWorld()->GetGameInstance()->GetSubsystem<UEatableEventDispatcher>();
	if (EatableEventDispatcher){
		EatableEventDispatcher->DispatchEatEvent(EEatEvent::Pellet, EatScore);
	}
}
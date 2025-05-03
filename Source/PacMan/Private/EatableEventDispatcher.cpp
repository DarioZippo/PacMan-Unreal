// Fill out your copyright notice in the Description page of Project Settings.


#include "EatableEventDispatcher.h"

void UEatableEventDispatcher::DispatchEatEvent(const EEatEvent& EatEvent){
	switch (EatEvent) {
		case EEatEvent::Dot:
			OnEatEvent.Broadcast();
			break;
		case EEatEvent::Pellet:
			OnEatEvent.Broadcast();
			OnEatPelletEvent.Broadcast();
			break;
		case EEatEvent::Ghost:
			OnEatEvent.Broadcast();
			OnEatGhostEvent.Broadcast();
		default:
			break;
	}
}

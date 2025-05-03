// Fill out your copyright notice in the Description page of Project Settings.


#include "EatableEventDispatcher.h"

void UEatableEventDispatcher::DispatchEatEvent(const EEatEvent& EatEvent, int ScoreIncrement){
	switch (EatEvent) {
		case EEatEvent::Dot:
			OnEatEvent.Broadcast(ScoreIncrement);
			break;
		case EEatEvent::Pellet:
			OnEatEvent.Broadcast(ScoreIncrement);
			OnEatPelletEvent.Broadcast();
			break;
		case EEatEvent::Ghost:
			OnEatEvent.Broadcast(ScoreIncrement);
			OnEatGhostEvent.Broadcast();
		default:
			break;
	}
}

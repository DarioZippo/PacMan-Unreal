// Fill out your copyright notice in the Description page of Project Settings.


#include "Dot.h"

#include "EatableEventDispatcher.h"

// Sets default values
ADot::ADot(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADot::BeginPlay(){
	Super::BeginPlay();
	
}

// Called every frame
void ADot::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

}

void ADot::Eat(){
	UEatableEventDispatcher* EatableEventDispatcher = GetWorld()->GetGameInstance()->GetSubsystem<UEatableEventDispatcher>();
	if (EatableEventDispatcher){
		EatableEventDispatcher->DispatchEatEvent(EEatEvent::Dot);
	}
}

bool ADot::GetIsEatable(){
	return true;
}

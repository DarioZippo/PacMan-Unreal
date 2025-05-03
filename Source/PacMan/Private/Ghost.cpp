// Fill out your copyright notice in the Description page of Project Settings.


#include "Ghost.h"

#include "Components/CapsuleComponent.h"

AGhost::AGhost(){
	Collider->OnComponentBeginOverlap.AddDynamic(this, &AGhost::OnEnterBoxOverlap);
	
	PrimaryActorTick.bCanEverTick = true;
}

void AGhost::BeginPlay(){
	Super::BeginPlay();
}

// Called every frame
void AGhost::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
}

void AGhost::OnEnterBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	
}
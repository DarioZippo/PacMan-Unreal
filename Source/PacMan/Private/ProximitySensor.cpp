// Fill out your copyright notice in the Description page of Project Settings.


#include "ProximitySensor.h"

#include "EGhostState.h"
#include "Ghost.h"
#include "PacMan_Character.h"
#include "Components/CapsuleComponent.h"

AProximitySensor::AProximitySensor(){
	PrimaryActorTick.bCanEverTick = true;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent")));
	
	Collider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collider"));
	Collider->SetupAttachment(RootComponent);

	Collider->SetLineThickness(1);
	Collider->ShapeColor = FColor::Yellow;
	Collider->bHiddenInGame = true;
	
	Collider->OnComponentBeginOverlap.AddDynamic(this, &AProximitySensor::OnEnterCapsuleOverlap);
}

void AProximitySensor::BeginPlay(){
	Super::BeginPlay();
}

void AProximitySensor::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

	if (Target){
		SetActorLocation(Target->GetActorLocation());
	}
}

void AProximitySensor::OnEnterCapsuleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (Target && Target->GhostState != EGhostState::Frightened){
		APacMan_Character* Character = Cast<APacMan_Character>(OtherActor);
		if (Character){
			//UE_LOG(LogTemp, Log, TEXT("In proximity to the player"));
			Target->SetGhostState(EGhostState::Scatter);
		}
	}
}

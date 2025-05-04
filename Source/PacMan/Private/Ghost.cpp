// Fill out your copyright notice in the Description page of Project Settings.


#include "Ghost.h"

#include "PacMan_Character.h"
#include "PaperSpriteComponent.h"
#include "Components/CapsuleComponent.h"

AGhost::AGhost(){
	PrimaryActorTick.bCanEverTick = true;
	
	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent")));

	GhostSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("GhostSprite"));
	GhostSprite->CanCharacterStepUpOn = ECB_No;
	GhostSprite->SetCollisionProfileName("NoCollision");
	GhostSprite->SetGenerateOverlapEvents(false);
	GhostSprite->SetupAttachment(RootComponent);
	
	Collider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collider"));
	Collider->SetupAttachment(RootComponent);

	Collider->SetLineThickness(1);
	Collider->ShapeColor = FColor::Red;
	Collider->bHiddenInGame = true;
	
	Collider->OnComponentBeginOverlap.AddDynamic(this, &AGhost::OnEnterCapsuleOverlap);
}

void AGhost::BeginPlay(){
	Super::BeginPlay();
}

// Called every frame
void AGhost::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
}

void AGhost::OnEnterCapsuleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	APacMan_Character* Character = Cast<APacMan_Character>(OtherActor);
	if (Character){
		Character->Die();
	}
}
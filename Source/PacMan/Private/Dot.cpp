// Fill out your copyright notice in the Description page of Project Settings.


#include "Dot.h"

#include "EatableEventDispatcher.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "PaperSpriteComponent.h"

// Sets default values
ADot::ADot(){
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent")));

	DotSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("DotSprite"));
	DotSprite->CanCharacterStepUpOn = ECB_No;
	DotSprite->SetCollisionProfileName("NoCollision");
	DotSprite->SetGenerateOverlapEvents(false);
	DotSprite->SetupAttachment(RootComponent);
	
	EatTriggerArea = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	EatTriggerArea->CanCharacterStepUpOn = ECB_No;
	EatTriggerArea->SetCollisionProfileName("Trigger");
	EatTriggerArea->SetGenerateOverlapEvents(true);
	EatTriggerArea->SetupAttachment(RootComponent);

	EatTriggerArea->SetLineThickness(1);
	EatTriggerArea->ShapeColor = FColor::Green;
	EatTriggerArea->bHiddenInGame = true;

	EatScore = 100;
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
	SetActorEnableCollision(false);
	SetActorHiddenInGame(true);

	UEatableEventDispatcher* EatableEventDispatcher = GetWorld()->GetGameInstance()->GetSubsystem<UEatableEventDispatcher>();
	if (EatableEventDispatcher){
		EatableEventDispatcher->DispatchEatEvent(EEatEvent::Dot, EatScore);
	}
}

bool ADot::GetIsEatable(){
	return true;
}

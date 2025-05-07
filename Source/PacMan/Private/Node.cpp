// Fill out your copyright notice in the Description page of Project Settings.


#include "Node.h"

#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"

ANode::ANode(){
	PrimaryActorTick.bCanEverTick = true;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent")));

	Sprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
	Sprite->CanCharacterStepUpOn = ECB_No;
	Sprite->SetCollisionProfileName("NoCollision");
	Sprite->SetGenerateOverlapEvents(false);
	Sprite->SetupAttachment(RootComponent);

	ShowSprite = true;
	
	TriggerArea = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	TriggerArea->CanCharacterStepUpOn = ECB_No;
	TriggerArea->SetCollisionProfileName("Trigger");
	TriggerArea->SetGenerateOverlapEvents(true);
	TriggerArea->SetupAttachment(RootComponent);

	TriggerArea->SetLineThickness(1);
	TriggerArea->ShapeColor = FColor::Orange;
	TriggerArea->bHiddenInGame = true;
}

void ANode::BeginPlay(){
	Super::BeginPlay();

	AvailableDirections.Empty();
	
	// We determine if the direction is available by box casting to see if
	// we hit a wall. The direction is added to list if available.
	CheckAvailableDirection(FVector2D(0, 1));
	CheckAvailableDirection(FVector2D(0, -1));
	CheckAvailableDirection(FVector2D(-1, 0));
	CheckAvailableDirection(FVector2D(1, 0));
}

void ANode::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
}

void ANode::CheckAvailableDirection(FVector2D Direction){
	// If no collider is hit then there is no obstacle in that direction
	FHitResult Hit;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	FVector Start = GetActorLocation();
	FVector End = Start + FVector(Direction, 0.f) * 7.5f;

	FVector BoxExtent = FVector(3.f, 3.f, 3.f);
	
	bool bHit = UKismetSystemLibrary::BoxTraceSingle(
		GetWorld(),
		Start,
		End,
		BoxExtent,
		FRotator(FQuat::Identity),
		TraceTypeQuery1,
		false,
		{},
		DrawDebugTrace ? EDrawDebugTrace::Persistent : EDrawDebugTrace::None,
		Hit,
		true
	);

	if (!bHit){
		if (!BannedDirections.Contains(Direction))
			AvailableDirections.Add(Direction);
	}
	else{
		if (ForcedDirections.Contains(Direction))
			AvailableDirections.Add(Direction);
	}
}

TArray<FVector2D> ANode::GetFilteredAvailableDirections(FVector2D GhostDirection){
	TArray<FVector2D> FilteredDirections;
    
	for (const FVector2D& Direction : AvailableDirections){
		if (Direction != -GhostDirection){
			FilteredDirections.Add(Direction);
		}
	}

	return FilteredDirections;
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "GhostAIController.h"

#include "VectorListContainer.h"
#include "EGhostState.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

AGhostAIController::AGhostAIController(){
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));

	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent")));
}

void AGhostAIController::OnPossess(APawn* InPawn){
	Super::OnPossess(InPawn);

	//UE_LOG(LogTemp, Warning, TEXT("On posses: %s"), *InPawn->GetName());
	
	if (BehaviorTree){
		if (UseBlackboard(BehaviorTree->BlackboardAsset, BlackboardComponent)){
			float RandomDelay = FMath::RandRange(0.0f, 5.0f);

			// Set a timer to randomize a delay between the ghosts starting
			GetWorld()->GetTimerManager().SetTimer(
				TimerHandle_DelayedStart,
				[this, InPawn]() { StartBehaviorTree(InPawn); },
				RandomDelay,
				false
			);
		}
	}
}

void AGhostAIController::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
}

void AGhostAIController::StartBehaviorTree(APawn* InPawn){
	BehaviorTreeComponent->StartTree(*BehaviorTree);

	ResetMovement();
}

void AGhostAIController::ResetMovement(){
	TArray<FVector2D> InitialAvailableDirections;
	InitialAvailableDirections.Add(FVector2D(1, 0));
	
	UVectorListContainer* VectorListContainer = NewObject<UVectorListContainer>();
	VectorListContainer->VectorArray = InitialAvailableDirections;
	BlackboardComponent->SetValueAsObject(*AvailableDirections, VectorListContainer);
}

void AGhostAIController::SetTargetBlackboard(AActor* TargetActor){
	BlackboardComponent->SetValueAsObject(*Target, TargetActor);
}

void AGhostAIController::SetScatterTargetBlackboard(AActor* ScatterActor){
	BlackboardComponent->SetValueAsObject(*ScatterTarget, ScatterActor);
}

void AGhostAIController::SetAvailableDirectionsBlackboard(UVectorListContainer* VectorListContainer){
	BlackboardComponent->SetValueAsObject(*AvailableDirections, VectorListContainer);
}

void AGhostAIController::SetGhostStateBlackboard(EGhostState NewGhostState){
	BlackboardComponent->SetValueAsEnum(*GhostState, static_cast<uint8>(NewGhostState));
}
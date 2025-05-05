// Fill out your copyright notice in the Description page of Project Settings.


#include "GhostAIController.h"

#include "Ghost.h"
#include "Node.h"
#include "PacMan_Character.h"
#include "VectorListContainer.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CapsuleComponent.h"

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
			StartBehaviorTree(InPawn);
		}
	}
}

void AGhostAIController::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
}

void AGhostAIController::StartBehaviorTree(APawn* InPawn){
	BehaviorTreeComponent->StartTree(*BehaviorTree);

	TArray<FVector2D> InitialAvailableDirections;
	InitialAvailableDirections.Add(FVector2D(0, 1));
	
	UVectorListContainer* VectorListContainer = NewObject<UVectorListContainer>();
	VectorListContainer->VectorArray = InitialAvailableDirections;
	BlackboardComponent->SetValueAsObject(*AvailableDirections, VectorListContainer);
}

void AGhostAIController::SetTargetBlackboard(AActor* TargetActor){
	BlackboardComponent->SetValueAsObject(*Target, TargetActor);
}

void AGhostAIController::SetAvailableDirectionsBlackboard(UVectorListContainer* VectorListContainer){
	BlackboardComponent->SetValueAsObject(*AvailableDirections, VectorListContainer);
}
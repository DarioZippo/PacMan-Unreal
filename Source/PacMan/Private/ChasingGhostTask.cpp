// Fill out your copyright notice in the Description page of Project Settings.


#include "ChasingGhostTask.h"
#include "AIController.h"
#include "VectorListContainer.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Actor.h"
#include "Ghost.h"
#include "GhostAIController.h"

UChasingGhostTask::UChasingGhostTask(){
	NodeName = "Chasing";
	bNotifyTick = true;
}

EBTNodeResult::Type UChasingGhostTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory){
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* AIController = OwnerComp.GetAIOwner();
	AActor* ControlledPawn = AIController ? AIController->GetPawn() : nullptr;

	if (!ControlledPawn){
		return EBTNodeResult::Failed;
	}

	UBlackboardComponent* BlackboardComponent = AIController->GetBlackboardComponent();

	Target = Cast<AActor>(BlackboardComponent->GetValueAsObject(TargetKey.SelectedKeyName));
	
	return EBTNodeResult::InProgress;
}

void UChasingGhostTask::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds){
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* AIController = OwnerComp.GetAIOwner();
	AGhost* ControlledGhost = Cast<AGhost>(AIController->GetPawn());
	
	UBlackboardComponent* BlackboardComponent = AIController->GetBlackboardComponent();

	if (ControlledGhost){
		UVectorListContainer* AvailableDirectionsContainer = Cast<UVectorListContainer>(BlackboardComponent->GetValueAsObject(AvailableDirectionsKey.SelectedKeyName));
		if (AvailableDirectionsContainer != nullptr){
			//UE_LOG(LogTemp, Log, TEXT("AvailableDirectionsContainer"));
			TArray<FVector2D> AvailableDirections = AvailableDirectionsContainer->VectorArray;
			
			FVector2D Direction = FVector2D::Zero();
			float MinDistance = TNumericLimits<float>::Max();

			// Find the available direction that comes closest to Pacman
			for (const FVector2D& AvailableDirection : AvailableDirections){
				//UE_LOG(LogTemp, Log, TEXT("X=%f, Y=%f"), AvailableDirection.X, AvailableDirection.Y);
				FVector NewPosition = ControlledGhost->GetActorLocation() + FVector(AvailableDirection.X, AvailableDirection.Y, 0.0f);
				float Distance = FVector::DistSquared(Target->GetActorLocation(), NewPosition);

				if (Distance < MinDistance){
					Direction = AvailableDirection;
					MinDistance = Distance;
				}
			}

			ControlledGhost->SetDirection(Direction);
			BlackboardComponent->ClearValue(AvailableDirectionsKey.SelectedKeyName);
		}
		else{
			if (ControlledGhost->CurrentDirection == FVector2D::Zero()){
				Cast<AGhostAIController>(AIController)->ResetMovement();
			}
		}
	}
}


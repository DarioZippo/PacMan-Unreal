// Fill out your copyright notice in the Description page of Project Settings.


#include "ChasingGhostTask.h"
#include "AIController.h"
#include "VectorListContainer.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Actor.h"
#include "Ghost.h"

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
			TArray<FVector2D> AvailableDirections = AvailableDirectionsContainer->VectorArray;
			
			FVector2D Direction = FVector2D::Zero();
			float MinDistance = TNumericLimits<float>::Max();

			// Find the available direction that moves closet to pacman
			for (const FVector2D& AvailableDirection : AvailableDirections){
				//UE_LOG(LogTemp, Display, TEXT("X=%f, Y=%f"), AvailableDirection.X, AvailableDirection.Y);
				
				// If the distance in this direction is less than the current
				// min distance then this direction becomes the new closest
				FVector NewPosition = ControlledGhost->GetActorLocation() + FVector(AvailableDirection.X, AvailableDirection.Y, 0.0f);
				float Distance = FVector::DistSquared(Target->GetActorLocation(), NewPosition);

				if (Distance < MinDistance){
					Direction = AvailableDirection;
					MinDistance = Distance;
				}
			}

			ControlledGhost->CurrentDirection = Direction;
			BlackboardComponent->ClearValue(AvailableDirectionsKey.SelectedKeyName);
		}
	}
}


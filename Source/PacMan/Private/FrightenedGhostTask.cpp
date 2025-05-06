// Fill out your copyright notice in the Description page of Project Settings.


#include "FrightenedGhostTask.h"

#include "AIController.h"
#include "Ghost.h"
#include "VectorListContainer.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"

UFrightenedGhostTask::UFrightenedGhostTask(){
	NodeName = "Frightened";
	bNotifyTick = true;
}

EBTNodeResult::Type UFrightenedGhostTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory){
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* AIController = OwnerComp.GetAIOwner();
	AActor* ControlledPawn = AIController ? AIController->GetPawn() : nullptr;

	if (!ControlledPawn){
		return EBTNodeResult::Failed;
	}
	
	return EBTNodeResult::InProgress;
}

void UFrightenedGhostTask::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds){
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* AIController = OwnerComp.GetAIOwner();
	AGhost* ControlledGhost = Cast<AGhost>(AIController->GetPawn());
	
	UBlackboardComponent* BlackboardComponent = AIController->GetBlackboardComponent();

	if (ControlledGhost){
		UVectorListContainer* AvailableDirectionsContainer = Cast<UVectorListContainer>(BlackboardComponent->GetValueAsObject(AvailableDirectionsKey.SelectedKeyName));
		if (AvailableDirectionsContainer && AvailableDirectionsContainer->VectorArray.Num() > 0){
			TArray<FVector2D> AvailableDirections = AvailableDirectionsContainer->VectorArray;
			
			int32 RandomIndex = UKismetMathLibrary::RandomIntegerInRange(0, AvailableDirections.Num() - 1);
			FVector2D RandomDirection = AvailableDirections[RandomIndex];
		
			ControlledGhost->CurrentDirection = RandomDirection;
			BlackboardComponent->ClearValue(AvailableDirectionsKey.SelectedKeyName);
		}
	}
}
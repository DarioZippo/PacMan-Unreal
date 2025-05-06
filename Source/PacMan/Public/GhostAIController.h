// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "VectorListContainer.h"
#include "GhostAIController.generated.h"

class UCapsuleComponent;
class UBehaviorTree;
class UBehaviorTreeComponent;
class UBlackboardComponent;

/**
 * 
 */
UCLASS()
class PACMAN_API AGhostAIController : public AAIController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "AI")
	UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere, Category = "AI")
	UBehaviorTreeComponent* BehaviorTreeComponent;

	UPROPERTY(EditAnywhere, Category = "AI")
	UBlackboardComponent* BlackboardComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Blackboard")
	FString Target;
	
	UPROPERTY(EditAnywhere, Category = "AI|Blackboard")
	FString AvailableDirections;

	UPROPERTY(EditAnywhere, Category = "AI|Blackboard")
	FString IsFrightened;
	
public:
	AGhostAIController();

	UFUNCTION(BlueprintCallable)
	void SetTargetBlackboard(AActor* TargetActor);
	
	UFUNCTION(BlueprintCallable)
	void SetAvailableDirectionsBlackboard(UVectorListContainer* VectorListContainer);

	UFUNCTION(BlueprintCallable)
	void SetIsFrightenedBlackboard(bool NewIsFrightened);

protected:
	virtual void Tick(float DeltaTime) override;
	virtual void OnPossess(APawn* InPawn) override;
	
	void StartBehaviorTree(APawn* InPawn);
};

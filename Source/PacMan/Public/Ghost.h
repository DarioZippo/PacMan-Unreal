// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Teleportable.h"
#include "GameFramework/Pawn.h"
#include "Ghost.generated.h"

class AGhostAIController;
class UCapsuleComponent;
class UPaperSpriteComponent;

UCLASS()
class PACMAN_API AGhost : public APawn, public ITeleportable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Blackboard")
	TObjectPtr<AActor> Target;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
	FVector2D CurrentDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float Speed;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UPaperSpriteComponent> GhostSprite;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UCapsuleComponent> Collider;
	
	bool IsTeleporting;
	
public:
	AGhost();
	
	UFUNCTION()
	void OnEnterCapsuleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
	virtual void SetIsTeleporting(bool NewIsTeleporting) override;
	
	UFUNCTION(BlueprintCallable)
	virtual bool GetIsTeleporting() override;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Eatable.h"
#include "Teleportable.h"
#include "CharacterPositionManager.h"
#include "GameFramework/Pawn.h"
#include "Ghost.generated.h"

enum class EGhostState : uint8;
class AGhostAIController;
class UCapsuleComponent;
class UPaperSpriteComponent;
class UPaperSprite;

UCLASS()
class PACMAN_API AGhost : public APawn, public ITeleportable, public IEatable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ESpawnableCharacter GhostName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Blackboard")
	TObjectPtr<AActor> Target;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Blackboard")
	TObjectPtr<AActor> ScatterTarget;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Blackboard")
	EGhostState GhostState;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	FVector2D CurrentDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float Speed;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UPaperSpriteComponent> GhostSprite;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UPaperSpriteComponent> EyesSprite;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual")
	TMap<FVector2D, UPaperSprite*> EyesSpritesMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UPaperSpriteComponent> FrightenedGhostSprite;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UCapsuleComponent> Collider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eatable", meta = (ClampMin = 0))
	int EatScore;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eatable")
	bool IsEatable;
	
	bool IsTeleporting;
	
public:
	AGhost();
	
	UFUNCTION()
	void OnEnterCapsuleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
	void SetDirection(FVector2D NewDirection);
	
	UFUNCTION(BlueprintCallable)
	virtual void SetIsTeleporting(bool NewIsTeleporting) override;
	
	UFUNCTION(BlueprintCallable)
	virtual bool GetIsTeleporting() override;
	
	UFUNCTION(BlueprintCallable)
	void SetGhostState(EGhostState NewGhostState);
	
	UFUNCTION(BlueprintCallable)
	virtual void Eat() override;

	UFUNCTION(BlueprintCallable)
	virtual bool GetIsEatable() override;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void Respawn();
};

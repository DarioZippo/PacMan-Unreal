// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ghost.generated.h"

class UCapsuleComponent;
class UPaperSpriteComponent;

UCLASS()
class PACMAN_API AGhost : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UPaperSpriteComponent> GhostSprite;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UCapsuleComponent> Collider;
	
public:
	AGhost();
	
	UFUNCTION()
	void OnEnterCapsuleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};

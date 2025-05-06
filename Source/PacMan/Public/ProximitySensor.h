// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProximitySensor.generated.h"

class AGhost;
class UCapsuleComponent;

UCLASS()
class PACMAN_API AProximitySensor : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UCapsuleComponent> Collider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AGhost* Target;
	
public:
	AProximitySensor();

	UFUNCTION()
	void OnEnterCapsuleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Eatable.h"
#include "GameFramework/Actor.h"
#include "Dot.generated.h"

class UPaperSpriteComponent;
class USphereComponent;
class UBoxComponent;

DECLARE_MULTICAST_DELEGATE(FButtonInteractionEvent);

UCLASS()
class PACMAN_API ADot : public AActor, public IEatable
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UPaperSpriteComponent> DotSprite;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UBoxComponent> EatTriggerArea;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Eatable")
	TObjectPtr<USphereComponent> InteractionCollider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eatable")
	float InteractionColliderRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eatable", meta = (ClampMin = 0))
	int EatScore;
	
public:
	ADot();
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable)
	virtual void Eat() override;

	UFUNCTION(BlueprintCallable)
	virtual bool GetIsEatable() override;
	
protected:
	virtual void BeginPlay() override;
};

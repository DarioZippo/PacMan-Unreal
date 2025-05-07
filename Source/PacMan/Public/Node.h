// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Node.generated.h"

class UBoxComponent;
class UPaperSpriteComponent;

UCLASS()
class PACMAN_API ANode : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Navigation")
	TArray<FVector2D> AvailableDirections;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Navigation")
	TArray<FVector2D> BannedDirections;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Navigation")
	TArray<FVector2D> ForcedDirections;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UPaperSpriteComponent> Sprite;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UBoxComponent> TriggerArea;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
	bool DrawDebugTrace;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
	bool ShowSprite;
public:	
	ANode();

	UFUNCTION(BlueprintCallable)
	void CheckAvailableDirection(FVector2D Direction);
	
	UFUNCTION(BlueprintCallable)
	TArray<FVector2D> GetFilteredAvailableDirections(FVector2D GhostDirection);
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};

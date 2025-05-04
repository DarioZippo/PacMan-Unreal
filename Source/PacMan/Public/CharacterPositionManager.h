// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CharacterPositionManager.generated.h"

UENUM(BlueprintType)
enum class ESpawnableCharacter : uint8 {  
	PacMan UMETA(DisplayName = "PacMan"),
	Shadow UMETA(DisplayName = "Shadow"),
	Speedy UMETA(DisplayName = "Speedy"),
	Bashful UMETA(DisplayName = "Bashful"),
	Pokey UMETA(DisplayName = "Pokey")
};

UCLASS()
class PACMAN_API ACharacterPositionManager : public AActor
{
	GENERATED_BODY()

public:
	static ACharacterPositionManager* Instance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Characters")
	TMap<ESpawnableCharacter, AActor*> CharacterPositionsMap;
	
public:	
	ACharacterPositionManager();

	UFUNCTION(BlueprintCallable)
	FTransform GetRespawnPosition(ESpawnableCharacter Character);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};

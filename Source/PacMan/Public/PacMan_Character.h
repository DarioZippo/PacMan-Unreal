// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "Respawnable.h"
#include "Teleportable.h"
#include "PacMan_Character.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_MULTICAST_DELEGATE(FDeathEvent);

UCLASS()
class PACMAN_API APacMan_Character : public APaperZDCharacter, public IRespawnable, public ITeleportable
{
	GENERATED_BODY()

public:
	static FDeathEvent OnDeathEvent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	FVector2D CurrentDirection;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	FVector2D NextDirection;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
	bool DrawDebugTrace;
	
	bool IsDead;
	bool IsTeleporting;
	
public:
	APacMan_Character();

	UFUNCTION()
	void OnEnterBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
	void Die();

	UFUNCTION(BlueprintCallable)
	void BroadcastDeath();
	
	UFUNCTION(BlueprintCallable)
	bool GetIsDead();

	UFUNCTION(BlueprintCallable)
	virtual void Respawn() override;

	UFUNCTION(BlueprintCallable)
	virtual void SetIsTeleporting(bool NewIsTeleporting) override;
	
	UFUNCTION(BlueprintCallable)
	virtual bool GetIsTeleporting() override;
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Move(const FInputActionValue& Value);
	void SetDirection(FVector2D NewDirection, bool Forced = false);
	bool Occupied(FVector2D Direction);
};

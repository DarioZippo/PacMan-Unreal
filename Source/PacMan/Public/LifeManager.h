// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LifeManager.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FLifesUpdateEvent, int);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PACMAN_API ULifeManager : public UActorComponent
{
	GENERATED_BODY()

public:
	static FLifesUpdateEvent OnLifesUpdateEvent;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lifes")
	int Lifes;
	
public:
	ULifeManager();
	
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UFUNCTION()
	void LoseLife();
};

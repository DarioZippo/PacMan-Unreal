// Fill out your copyright notice in the Description page of Project Settings.


#include "PacMan_Character.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PaperFlipbookComponent.h"

APacMan_Character::APacMan_Character(){
}

void APacMan_Character::BeginPlay(){
	Super::BeginPlay();

	MovementVector = FVector2D(1, 0);
}

void APacMan_Character::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
	
	if (this->GetController() != nullptr){ 
		AddMovementInput(GetActorRightVector(), -MovementVector.Y);
		AddMovementInput(GetActorForwardVector(), MovementVector.X);

		if (!MovementVector.IsZero()){
			FRotator CurrentRotation = GetActorRotation();
		
			float RotationAngle = FMath::Atan2(-MovementVector.Y, MovementVector.X) * (180.0f / PI);
			FRotator NewRotation(CurrentRotation.Pitch, RotationAngle, CurrentRotation.Roll);
			SetActorRotation(NewRotation);
		}
	}
}

void APacMan_Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent){
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController())){
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())){
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)){
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APacMan_Character::Move);
	}
	else{
		UE_LOG(LogTemp, Error, TEXT("Failed to find an Enhanced Input component!"));
	}
}

void APacMan_Character::Move(const FInputActionValue& Value){
	FVector2D MovementInputVector = Value.Get<FVector2D>();

	UE_LOG(LogTemp, Log, TEXT("Movement Value: X=%f, Y=%f"), MovementInputVector.X, MovementInputVector.Y);

	MovementVector = MovementInputVector;
}
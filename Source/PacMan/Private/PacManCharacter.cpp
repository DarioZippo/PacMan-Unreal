// Fill out your copyright notice in the Description page of Project Settings.


#include "PacManCharacter.h"

#include "CharacterPositionManager.h"
#include "Dot.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PaperSpriteComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"

FDeathEvent APacManCharacter::OnDeathEvent;

APacManCharacter::APacManCharacter(){
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APacManCharacter::OnEnterBoxOverlap);
	
	DrawDebugTrace = false;
	IsDead = false;
}

void APacManCharacter::BeginPlay(){
	Super::BeginPlay();

	CurrentDirection = FVector2D(1, 0);
}

void APacManCharacter::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

	FRotator CurrentRotation = GetActorRotation();
		
	float RotationAngle = FMath::Atan2(CurrentDirection.Y, CurrentDirection.X) * (180.0f / PI);
	FRotator NewRotation(CurrentRotation.Pitch, RotationAngle, CurrentRotation.Roll);

	if (IsDead){
		SetActorRotation(NewRotation + FRotator(0.f, -90.f, 0.f));
		GetMovementComponent()->StopMovementImmediately();
		return;
	}
	
	if (NextDirection != FVector2D(0, 0)){
        SetDirection(NextDirection);
    }
	if (this->GetController() != nullptr){ 
		AddMovementInput(GetActorRightVector(), CurrentDirection.Y);
		AddMovementInput(GetActorForwardVector(), CurrentDirection.X);

		SetActorRotation(NewRotation);
	}
}

void APacManCharacter::OnEnterBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OtherActor->Implements<UEatable>()){
		IEatable* EatableActor = Cast<IEatable>(OtherActor);
		EatableActor->Eat();
	}
}

void APacManCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent){
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController())){
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())){
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)){
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APacManCharacter::Move);
	}
	else{
		UE_LOG(LogTemp, Error, TEXT("Failed to find an Enhanced Input component!"));
	}
}

void APacManCharacter::Move(const FInputActionValue& Value){
	FVector2D MovementInputDirection = Value.Get<FVector2D>();
	NextDirection = FVector2D(MovementInputDirection.X, -MovementInputDirection.Y);
}

void APacManCharacter::SetDirection(FVector2D NewDirection, bool Forced){
	// Only set the direction if the tile in that direction is available
	// otherwise we set it as the next direction so it'll automatically be
	// set when it does become available
	if (Forced || !Occupied(NewDirection)){
		CurrentDirection = NewDirection;
		NextDirection = FVector2D::ZeroVector;
	}
	else{
		NextDirection = NewDirection;
	}
}

bool APacManCharacter::Occupied(FVector2D Direction){
	// If no collider is hit then there is no obstacle in that direction
	FHitResult Hit;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	FVector Start = GetActorLocation();
	FVector End = Start + FVector(Direction, 0.f) * 7.5f;

	FVector BoxExtent = FVector(3.f, 3.f, 3.f);
	
	bool bHit = UKismetSystemLibrary::BoxTraceSingle(
		GetWorld(),
		Start,
		End,
		BoxExtent,
		FRotator(FQuat::Identity),
		TraceTypeQuery1,
		false,
		{},
		DrawDebugTrace ? EDrawDebugTrace::Persistent : EDrawDebugTrace::None,
		Hit,
		true
	);

	return bHit;
}

void APacManCharacter::Die(){
	IsDead = true;
}

void APacManCharacter::BroadcastDeath(){
	OnDeathEvent.Broadcast();

	Respawn();
}

bool APacManCharacter::GetIsDead(){
	return IsDead;
}

void APacManCharacter::Respawn(){
	FTransform RespawnPosition = ACharacterPositionManager::Instance->GetRespawnPosition(ESpawnableCharacter::PacMan);
	SetActorTransform(RespawnPosition);
	CurrentDirection = FVector2D(1, 0);
	
	IsDead = false;
}

void APacManCharacter::SetIsTeleporting(bool NewIsTeleporting){
	IsTeleporting = NewIsTeleporting;
}

bool APacManCharacter::GetIsTeleporting(){
	return IsTeleporting;
}
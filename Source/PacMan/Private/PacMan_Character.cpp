// Fill out your copyright notice in the Description page of Project Settings.


#include "PacMan_Character.h"

#include "CharacterPositionManager.h"
#include "Dot.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PaperSpriteComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"

FDeathEvent APacMan_Character::OnDeathEvent;

APacMan_Character::APacMan_Character(){
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APacMan_Character::OnEnterBoxOverlap);
	
	DrawDebugTrace = false;
	IsDead = false;
}

void APacMan_Character::BeginPlay(){
	Super::BeginPlay();

	CurrentDirection = FVector2D(1, 0);
}

void APacMan_Character::Tick(float DeltaTime){
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

void APacMan_Character::OnEnterBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OtherActor->Implements<UEatable>()){
		IEatable* EatableActor = Cast<IEatable>(OtherActor);
		EatableActor->Eat();
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
	FVector2D MovementInputDirection = Value.Get<FVector2D>();
	NextDirection = FVector2D(MovementInputDirection.X, -MovementInputDirection.Y);
}

void APacMan_Character::SetDirection(FVector2D NewDirection, bool Forced){
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

bool APacMan_Character::Occupied(FVector2D Direction){
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

void APacMan_Character::Die(){
	IsDead = true;
	UE_LOG(LogTemp, Log, TEXT("DEAD"));
}

void APacMan_Character::BroadcastDeath(){
	OnDeathEvent.Broadcast();

	Respawn();
}

bool APacMan_Character::GetIsDead(){
	return IsDead;
}

void APacMan_Character::Respawn(){
	FTransform RespawnPosition = ACharacterPositionManager::Instance->GetRespawnPosition(ESpawnableCharacter::PacMan);
	SetActorTransform(RespawnPosition);
	
	IsDead = false;
}

void APacMan_Character::SetIsTeleporting(bool NewIsTeleporting){
	IsTeleporting = NewIsTeleporting;
}

bool APacMan_Character::GetIsTeleporting(){
	return IsTeleporting;
}
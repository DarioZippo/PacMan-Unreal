// Fill out your copyright notice in the Description page of Project Settings.


#include "Ghost.h"

#include "CharacterPositionManager.h"
#include "EatableEventDispatcher.h"
#include "EGhostState.h"
#include "GhostAIController.h"
#include "Node.h"
#include "PacMan_Character.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"
#include "VectorListContainer.h"
#include "Components/CapsuleComponent.h"

AGhost::AGhost(){
	PrimaryActorTick.bCanEverTick = true;
	
	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent")));

	GhostSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("GhostSprite"));
	GhostSprite->CanCharacterStepUpOn = ECB_No;
	GhostSprite->SetCollisionProfileName("NoCollision");
	GhostSprite->SetGenerateOverlapEvents(false);
	GhostSprite->SetupAttachment(RootComponent);

	for (int i = 0; i < 4; i++){
		EyesSpritesMap.Add(FVector2D(1, 0), nullptr);
		EyesSpritesMap.Add(FVector2D(-1, 0), nullptr);
		EyesSpritesMap.Add(FVector2D(0, 1), nullptr);
		EyesSpritesMap.Add(FVector2D(0, -1), nullptr);
	}
	
	EyesSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("EyesSprite"));
	EyesSprite->CanCharacterStepUpOn = ECB_No;
	EyesSprite->SetCollisionProfileName("NoCollision");
	EyesSprite->SetGenerateOverlapEvents(false);
	EyesSprite->SetSprite(EyesSpritesMap[FVector2D(1, 0)]);
	EyesSprite->SetupAttachment(GhostSprite);

	FrightenedGhostSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("FrightenedGhostSprite"));
	FrightenedGhostSprite->CanCharacterStepUpOn = ECB_No;
	FrightenedGhostSprite->SetCollisionProfileName("NoCollision");
	FrightenedGhostSprite->SetGenerateOverlapEvents(false);
	FrightenedGhostSprite->SetVisibility(false);
	FrightenedGhostSprite->SetupAttachment(RootComponent);
	
	Collider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collider"));
	Collider->SetupAttachment(RootComponent);

	Collider->SetLineThickness(1);
	Collider->ShapeColor = FColor::Red;
	Collider->bHiddenInGame = true;
	
	Collider->OnComponentBeginOverlap.AddDynamic(this, &AGhost::OnEnterCapsuleOverlap);

	GhostState = EGhostState::Chase;
	Speed = 1;
	EatScore = 100;
	IsEatable = false;
}

void AGhost::BeginPlay(){
	Super::BeginPlay();

	UEatableEventDispatcher* EatableEventDispatcher = GetWorld()->GetGameInstance()->GetSubsystem<UEatableEventDispatcher>();
	if (EatableEventDispatcher){
		EatableEventDispatcher->OnEatPelletEvent.AddUObject(this, &AGhost::SetGhostState, EGhostState::Frightened);
	}

	AGhostAIController* GhostController = Cast<AGhostAIController>(GetController());
	if (GhostController){
		GhostController->SetTargetBlackboard(Target);
		GhostController->SetScatterTargetBlackboard(ScatterTarget);
	}
	else{
		UE_LOG(LogTemp, Error, TEXT("AIController NULL"));
	}
	
	SetGhostState(GhostState);
}

// Called every frame
void AGhost::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

	FVector Movement = FVector(CurrentDirection.X, CurrentDirection.Y, 0.0f) * Speed * DeltaTime;
	AddActorWorldOffset(Movement, true);
}

void AGhost::OnEnterCapsuleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                   const FHitResult& SweepResult)
{
	APacMan_Character* Character = Cast<APacMan_Character>(OtherActor);
	if (!IsEatable && Character){
		UE_LOG(LogTemp, Warning, TEXT("Collider Player"));
		Character->Die();
	}
	else{
		ANode* Node = Cast<ANode>(OtherActor);
		if (Node){
			UVectorListContainer* VectorListContainer = NewObject<UVectorListContainer>();
			VectorListContainer->VectorArray = Node->GetFilteredAvailableDirections(CurrentDirection);

			AGhostAIController* GhostController = Cast<AGhostAIController>(GetController());
			if (GhostController){
				//UE_LOG(LogTemp, Log, TEXT("On Node"));
				GhostController->SetAvailableDirectionsBlackboard(VectorListContainer);
			}
			else{
				UE_LOG(LogTemp, Error, TEXT("AIController NULL"));
			}
		}
	}
}

void AGhost::SetDirection(FVector2D NewDirection){	
	CurrentDirection = NewDirection;
	if (EyesSpritesMap.Contains(CurrentDirection)){
		EyesSprite->SetSprite(EyesSpritesMap[CurrentDirection]);
	}
	else{
		UE_LOG(LogTemp, Warning, TEXT("Sprite not contained for NewDirection: %s | CurrentDirection: %s"), *NewDirection.ToString(), *CurrentDirection.ToString());
	}
}

void AGhost::SetIsTeleporting(bool NewIsTeleporting){
	IsTeleporting = NewIsTeleporting;
}

bool AGhost::GetIsTeleporting(){
	return IsTeleporting;
}

void AGhost::SetGhostState(EGhostState NewGhostState){
	GhostState = NewGhostState;

	bool IsFrightened = GhostState == EGhostState::Frightened;
	IsEatable = IsFrightened;
	
	GhostSprite->SetVisibility(!IsFrightened);
	EyesSprite->SetVisibility(!IsFrightened);
	FrightenedGhostSprite->SetVisibility(IsFrightened);
	
	AGhostAIController* GhostController = Cast<AGhostAIController>(GetController());
	if (GhostController){
		GhostController->SetGhostStateBlackboard(GhostState);
	}
	else{
		UE_LOG(LogTemp, Error, TEXT("AIController NULL"));
	}
}

void AGhost::Eat(){
	if (IsEatable){
		UEatableEventDispatcher* EatableEventDispatcher = GetWorld()->GetGameInstance()->GetSubsystem<UEatableEventDispatcher>();
		if (EatableEventDispatcher){
			EatableEventDispatcher->DispatchEatEvent(EEatEvent::Dot, EatScore);
		}
		Respawn();
	}
}

bool AGhost::GetIsEatable(){
	return IsEatable;
}

void AGhost::Respawn(){
	FTransform HousePosition = ACharacterPositionManager::Instance->GetRespawnPosition(GhostName);
	SetActorLocation(HousePosition.GetLocation());

	AGhostAIController* GhostController = Cast<AGhostAIController>(GetController());
	if (GhostController){
		GhostController->ResetMovement();
	}
	else{
		UE_LOG(LogTemp, Error, TEXT("AIController NULL"));
	}
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "Ghost.h"

#include "CharacterPositionManager.h"
#include "EatableEventDispatcher.h"
#include "GhostAIController.h"
#include "Node.h"
#include "PacMan_Character.h"
#include "PaperSpriteComponent.h"
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
	
	Collider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collider"));
	Collider->SetupAttachment(RootComponent);

	Collider->SetLineThickness(1);
	Collider->ShapeColor = FColor::Red;
	Collider->bHiddenInGame = true;
	
	Collider->OnComponentBeginOverlap.AddDynamic(this, &AGhost::OnEnterCapsuleOverlap);

	IsFrightened = false;
	Speed = 1;
	EatScore = 100;
	IsEatable = false;
}

void AGhost::BeginPlay(){
	Super::BeginPlay();

	UEatableEventDispatcher* EatableEventDispatcher = GetWorld()->GetGameInstance()->GetSubsystem<UEatableEventDispatcher>();
	if (EatableEventDispatcher){
		EatableEventDispatcher->OnEatPelletEvent.AddUObject(this, &AGhost::SetIsFrightened, true);
	}
	
	CurrentDirection = FVector2D(0, 1);
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

void AGhost::SetIsTeleporting(bool NewIsTeleporting){
	IsTeleporting = NewIsTeleporting;
}

bool AGhost::GetIsTeleporting(){
	return IsTeleporting;
}

void AGhost::SetIsFrightened(bool NewIsFrightened){
	IsFrightened = NewIsFrightened;
	IsEatable = IsFrightened;
	
	AGhostAIController* GhostController = Cast<AGhostAIController>(GetController());
	if (GhostController){
		UE_LOG(LogTemp, Log, TEXT("FRIGHTENED"));
		GhostController->SetIsFrightenedBlackboard(NewIsFrightened);
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

		FTransform HousePosition = ACharacterPositionManager::Instance->GetRespawnPosition(GhostName);
		SetActorLocation(HousePosition.GetLocation());
	}
}

bool AGhost::GetIsEatable(){
	return IsEatable;
}

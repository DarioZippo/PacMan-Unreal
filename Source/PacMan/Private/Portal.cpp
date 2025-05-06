// Fill out your copyright notice in the Description page of Project Settings.


#include "Portal.h"

#include "PacMan_Character.h"
#include "Components/BoxComponent.h"

APortal::APortal(){
	PrimaryActorTick.bCanEverTick = true;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent")));

	TriggerArea = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerArea"));
	TriggerArea->CanCharacterStepUpOn = ECB_No;
	TriggerArea->SetCollisionProfileName("Trigger");
	TriggerArea->SetGenerateOverlapEvents(true);
	TriggerArea->SetupAttachment(RootComponent);

	TriggerArea->SetLineThickness(1);
	TriggerArea->ShapeColor = FColor::Purple;
	TriggerArea->bHiddenInGame = true;
	
	TriggerArea->OnComponentBeginOverlap.AddDynamic(this, &APortal::OnEnterBoxOverlap);

	ExitAreaFront = CreateDefaultSubobject<UBoxComponent>(TEXT("ExitAreaFront"));
	ExitAreaFront->CanCharacterStepUpOn = ECB_No;
	ExitAreaFront->SetCollisionProfileName("Trigger");
	ExitAreaFront->SetGenerateOverlapEvents(true);
	ExitAreaFront->SetupAttachment(RootComponent);

	ExitAreaFront->SetLineThickness(1);
	ExitAreaFront->ShapeColor = FColor::Magenta;
	ExitAreaFront->bHiddenInGame = true;
	
	ExitAreaFront->OnComponentBeginOverlap.AddDynamic(this, &APortal::OnEnterExitAreaOverlap);

	ExitAreaBack = CreateDefaultSubobject<UBoxComponent>(TEXT("ExitAreaBack"));
	ExitAreaBack->CanCharacterStepUpOn = ECB_No;
	ExitAreaBack->SetCollisionProfileName("Trigger");
	ExitAreaBack->SetGenerateOverlapEvents(true);
	ExitAreaBack->SetupAttachment(RootComponent);

	ExitAreaBack->SetLineThickness(1);
	ExitAreaBack->ShapeColor = FColor::Magenta;
	ExitAreaBack->bHiddenInGame = true;
	
	ExitAreaBack->OnComponentBeginOverlap.AddDynamic(this, &APortal::OnEnterExitAreaOverlap);
}

void APortal::BeginPlay(){
	Super::BeginPlay();
}

void APortal::OnConstruction(const FTransform& Transform){
	Super::OnConstruction(Transform);

	if (LinkedPortal != nullptr){
		LinkedPortal->SetLinkedPortal(this);
	}
}

void APortal::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
}

void APortal::SetLinkedPortal(APortal* NewPortal){
	LinkedPortal = NewPortal;
}

void APortal::Teleport(AActor* ActorToTeleport){
	ActorToTeleport->SetActorLocation(LinkedPortal->GetActorLocation());
}

void APortal::OnEnterBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OtherActor->Implements<UTeleportable>()){
		ITeleportable* TeleportableActor = Cast<ITeleportable>(OtherActor);
		if (!TeleportableActor->GetIsTeleporting()){
			TeleportableActor->SetIsTeleporting(true);
			Teleport(OtherActor);
		}
	}
}

void APortal::OnEnterExitAreaOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                            const FHitResult& SweepResult)
{
	if (OtherActor->Implements<UTeleportable>()){
		ITeleportable* TeleportableActor = Cast<ITeleportable>(OtherActor);
		TeleportableActor->SetIsTeleporting(false);
	}
}

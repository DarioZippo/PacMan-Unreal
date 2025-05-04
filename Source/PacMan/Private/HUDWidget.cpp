// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDWidget.h"

#include <string>

#include "LifeManager.h"
#include "ScoreManager.h"
#include "Components/TextBlock.h"

void UHUDWidget::NativeConstruct(){
	Super::NativeConstruct();

	UScoreManager::OnScoreUpdateEvent.AddUObject(this, &UHUDWidget::UpdateScore);
	ULifeManager::OnLifesUpdateEvent.AddUObject(this, &UHUDWidget::UpdateLifes);
}

void UHUDWidget::UpdateScore(int NewScore){
	ScoreText->SetText(FText::AsNumber(NewScore));
}

void UHUDWidget::UpdateLifes(int NewLifes){
	LifesText->SetText(FText::FromString(TEXT("x") + FString::FromInt(NewLifes)));
}
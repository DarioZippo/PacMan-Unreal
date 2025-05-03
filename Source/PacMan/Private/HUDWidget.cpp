// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDWidget.h"

#include <string>

#include "ScoreManager.h"
#include "Components/TextBlock.h"

void UHUDWidget::NativeConstruct(){
	Super::NativeConstruct();

	UScoreManager::OnScoreUpdateEvent.AddUObject(this, &UHUDWidget::UpdateScore);
}

void UHUDWidget::UpdateScore(int NewScore){
	ScoreText->SetText(FText::AsNumber(NewScore));
}
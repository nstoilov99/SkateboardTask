// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SkateboardOverlay.h"

#include "Components/TextBlock.h"
#include "UI/HUD/SkateboardHUD.h"

void USkateboardOverlay::NativeConstruct()
{
	Super::NativeConstruct();
	if (APlayerController* PlayerController = GetOwningPlayer())
	{
		if (ASkateboardHUD* HUD = Cast<ASkateboardHUD>(PlayerController->GetHUD()))
		{
			HUD->OnAddPointsDelegate.BindDynamic(this, &USkateboardOverlay::SetScore);
		}
	}
}

void USkateboardOverlay::SetScore(const FString& Score)
{
	ScoreTextBlock->SetText(FText::FromString(Score));
}

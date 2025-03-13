// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/SkateboardHUD.h"
#include "UI/SkateboardOverlay.h"
#include "Blueprint/UserWidget.h"

void ASkateboardHUD::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* OwningPlayerController = GetOwningPlayerController();
	SkateboardOverlay = CreateWidget<USkateboardOverlay>(OwningPlayerController, SkateboardOverlayClass);
	if (IsValid(SkateboardOverlay))
	{
		SkateboardOverlay->AddToViewport();
	}
}

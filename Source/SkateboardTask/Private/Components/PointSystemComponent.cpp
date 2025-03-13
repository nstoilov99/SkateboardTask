// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PointSystemComponent.h"

#include "GameFramework/PlayerController.h"


UPointSystemComponent::UPointSystemComponent()
{
}

void UPointSystemComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UPointSystemComponent::AddPoints(int32 PointsToAdd)
{
	Points += PointsToAdd;
	if (ASkateboardHUD* SkateboardHUD = GetSkateboardHUD(); IsValid(SkateboardHUD))
	{
		SkateboardHUD->OnAddPointsDelegate.ExecuteIfBound(FString::FromInt(Points));
	}
		
}

ASkateboardHUD* UPointSystemComponent::GetSkateboardHUD()
{
	if (GetOwner())
	{
		if (APlayerController* PlayerController = Cast<APlayerController>(GetOwner()->GetInstigatorController()))
		{
			return Cast<ASkateboardHUD>(PlayerController->GetHUD());
		}
	}
	return nullptr;
}

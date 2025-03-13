// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SkateboardHUD.generated.h"

class USkateboardOverlay;
/**
 * 
 */
UCLASS()
class SKATEBOARDTASK_API ASkateboardHUD : public AHUD
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<USkateboardOverlay> SkateboardOverlayClass;
	
protected:

	virtual void BeginPlay() override;
	
private:

	UPROPERTY()
	TObjectPtr<USkateboardOverlay> SkateboardOverlay;
};

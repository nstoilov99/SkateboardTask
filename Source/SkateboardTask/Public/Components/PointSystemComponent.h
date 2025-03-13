// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UI/HUD/SkateboardHUD.h"
#include "PointSystemComponent.generated.h"


class ASkateboardHUD;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SKATEBOARDTASK_API UPointSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPointSystemComponent();

	UFUNCTION(BlueprintCallable)
	void AddPoints(int32 PointsToAdd);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	int32 Points;

	ASkateboardHUD* GetSkateboardHUD();
};

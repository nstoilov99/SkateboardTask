// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SkateboardOverlay.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class SKATEBOARDTASK_API USkateboardOverlay : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;	
private:
	
	UFUNCTION()
	void SetScore(const FString& Score);
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ScoreTextBlock;
};

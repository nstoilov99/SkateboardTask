// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/SkateboardGameMode.h"

#include "Character/SkateboardCharacter.h"

ASkateboardGameMode::ASkateboardGameMode()
{
	DefaultPawnClass = ASkateboardCharacter::StaticClass();
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/SkateObstacleActor.h"
#include "Character/SkateboardCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/PointSystemComponent.h"

ASkateObstacleActor::ASkateObstacleActor()
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	SetRootComponent(StaticMeshComponent);
	
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetBoxExtent(FVector(50.0f)); // Set the size of the box
	BoxComponent->SetCollisionProfileName(TEXT("Trigger"));
	BoxComponent->SetupAttachment(RootComponent);
	
}

void ASkateObstacleActor::BeginPlay()
{
	Super::BeginPlay();
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ASkateObstacleActor::OnBeginOverlap);
}

void ASkateObstacleActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ASkateboardCharacter* SkateboardCharacter = Cast<ASkateboardCharacter>(OtherActor))
	{
		if (SkateboardCharacter->IsJumping())
		{
			SkateboardCharacter->PointSystemComponent->AddPoints(PointsToAdd);
		}
	}
}

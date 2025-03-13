// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SkateboardCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/PointSystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "ScreenPass.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values
ASkateboardCharacter::ASkateboardCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 90.0f);
	
	// Create and attach the camera boom
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;
	
	// Create and attach the follow camera
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;

	// Create and attach the skateboard mesh
	SkateboardMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkateboardMesh"));
	SkateboardMesh->SetupAttachment(RootComponent);
	SkateboardMesh->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	SkateboardMesh->SetRelativeScale3D(FVector(0.1f, 0.1f, 0.1f));
	
	PointSystemComponent = CreateDefaultSubobject<UPointSystemComponent>(TEXT("PointsSystemComponent"));
	
	
	GetCharacterMovement()->bOrientRotationToMovement= true;
	GetCharacterMovement()->JumpZVelocity = 600.0f;
	GetCharacterMovement()->AirControl = 0.2f;
	PrimaryActorTick.bCanEverTick = false;
}

float ASkateboardCharacter::GetUserAccelerating()
{
	FVector Acceleration = GetCharacterMovement()->GetCurrentAcceleration();
	FVector ForwardDirection = FVector(Acceleration.X, 0.0f, 0.0f);
	return ForwardDirection.Length();
}

bool ASkateboardCharacter::IsJumping()
{
	return GetCharacterMovement()->IsFalling();
}

// Called when the game starts or when spawned
void ASkateboardCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	GetWorld()->GetTimerManager().SetTimer(
		SkateboardTimerHandle,
		this,
		&ASkateboardCharacter::AlignSkateboardToGround,
		FunctionLoopRate,
		true
	);
}
void ASkateboardCharacter::AlignSkateboardToGround()
{
	FVector FWHitLocation = WheelTraceHitLocation(FrontWheelSocketName);
	FVector BWHitLocation = WheelTraceHitLocation(BackWheelSocketName);
	FRotator NewSkateboardRotator = UKismetMathLibrary::FindLookAtRotation(BWHitLocation, FWHitLocation);
	SkateboardMesh->SetWorldRotation(FRotator(NewSkateboardRotator.Pitch, SkateboardMesh->GetComponentRotation().Yaw, SkateboardMesh->GetComponentRotation().Roll));
}

FVector ASkateboardCharacter::WheelTraceHitLocation(const FName& SocketName)
{
	FHitResult HitResult;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, this);
	FVector StartLocation = SkateboardMesh->GetSocketLocation(SocketName) + FVector(0.0f, 0.0f, SkateboardTraceOffset);;
	FVector EndLocation = StartLocation + FVector(0.0f, 0.0f, -SkateboardTraceOffset);
	if (UKismetSystemLibrary::LineTraceSingle(this,
		StartLocation,
		EndLocation,
		UEngineTypes::ConvertToTraceType(ECC_Camera),
		false,
		TArray<AActor*>(),
		EDrawDebugTrace::None,
		HitResult,
		true))
	{
		return HitResult.Location;
	}
	return SkateboardMesh->GetSocketLocation(SocketName);
}


// Called to bind functionality to input
void ASkateboardCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ThisClass::Look);
	}
}

void ASkateboardCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		MovingForward = MovementVector.Y;
		// get forward vector
		const FVector ForwardDirection = SkateboardMesh->GetForwardVector();
	
		// get right vector 
		const FVector RightDirection = SkateboardMesh->GetRightVector();

		// add movement
		LerpAccelerate = UKismetMathLibrary::Lerp(LerpAccelerate, MovementVector.Y, 0.01);
		AddMovementInput(ForwardDirection, LerpAccelerate);
		AddMovementInput(RightDirection, MovementVector.X * TurnRate);
	}
}

void ASkateboardCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ASkateboardCharacter::OnJumped_Implementation()
{
	Super::OnJumped_Implementation();
}


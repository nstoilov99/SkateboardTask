// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SkateboardCharacter.generated.h"

class UPointSystemComponent;
class UCameraComponent;
class USpringArmComponent;
class UInputMappingContext;
class UInputAction;
class UStaticMesh;
struct FInputActionValue;

UCLASS()
class SKATEBOARDTASK_API ASkateboardCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASkateboardCharacter();

	UFUNCTION(BlueprintCallable)
	float GetUserAccelerating();

	UFUNCTION(BlueprintCallable)
	bool IsJumping();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UPointSystemComponent> PointSystemComponent;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	virtual void OnJumped_Implementation() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = Camera)
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(EditDefaultsOnly, Category = Camera)
	TObjectPtr<UCameraComponent> CameraComponent;
	
	UPROPERTY(EditDefaultsOnly, Category = Input)
	TObjectPtr<UInputMappingContext> DefaultMappingContext;
	
	UPROPERTY(EditDefaultsOnly, Category = Input)
	TObjectPtr<UInputAction> JumpAction;
	
	UPROPERTY(EditDefaultsOnly, Category = Input)
	TObjectPtr<UInputAction> MoveAction;
	
	UPROPERTY(EditDefaultsOnly, Category = Input)
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(Category=Character, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> SkateboardMesh;

	FTimerHandle SkateboardTimerHandle;

	UPROPERTY(EditDefaultsOnly, Category = Skateboard)
	FName FrontWheelSocketName;
	
	UPROPERTY(EditDefaultsOnly, Category = Skateboard)
	FName BackWheelSocketName;
	
	UPROPERTY(EditDefaultsOnly, Category = Skateboard)
	float InterpSpeedToGround{10.f};
	
	UPROPERTY(EditDefaultsOnly, Category = Skateboard)
	float SkateboardTraceOffset{30.f};

	float LerpAccelerate{0.f};

	float MovingForward{0.f};
	
	UPROPERTY(EditDefaultsOnly, Category = Skateboard)
	float TurnRate = 0.05f;
	
	UPROPERTY(EditDefaultsOnly, Category = Skateboard)
	float FunctionLoopRate{0.03f};

	UFUNCTION()
	void AlignSkateboardToGround();

	UFUNCTION()
	FVector WheelTraceHitLocation(const FName& SocketName);
	
};
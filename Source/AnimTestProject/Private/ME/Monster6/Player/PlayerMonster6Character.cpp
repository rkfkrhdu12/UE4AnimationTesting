// Fill out your copyright notice in the Description page of Project Settings.


#include "ME/Monster6/Player/PlayerMonster6Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

APlayerMonster6Character::APlayerMonster6Character()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	CameraArmComponent->SetupAttachment(GetRootComponent());
	CameraArmComponent->TargetArmLength = 300.f;

	CameraArmComponent->bInheritPitch = false;
	CameraArmComponent->bInheritYaw = true;
	CameraArmComponent->bInheritRoll = false;

	CameraArmComponent->bEnableCameraLag = true;
	CameraArmComponent->CameraLagSpeed = 10.f;

	CameraArmComponent->bEnableCameraRotationLag = true;
	CameraArmComponent->CameraRotationLagSpeed = 30.f;

	FVector CameraArmLocation = FVector::ZeroVector;
	CameraArmLocation.X = -4.3f;
	CameraArmLocation.Y = 10.f;
	CameraArmLocation.Z = 50.f;
	FRotator CameraArmRotate = FRotator(340.0f, 0, .0f);
	CameraArmComponent->SetRelativeLocationAndRotation(CameraArmLocation, CameraArmRotate);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(CameraArmComponent);
}

void APlayerMonster6Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMonster6Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMonster6Character::MoveRight);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AMonster6Character::Attack);
}

bool APlayerMonster6Character::IsValidCameraArm() const
{
	return CameraArmComponent != nullptr && CameraArmComponent->IsValidLowLevelFast();
}

bool APlayerMonster6Character::IsValidCamera() const
{
	return CameraComponent != nullptr && CameraComponent->IsValidLowLevelFast();
}

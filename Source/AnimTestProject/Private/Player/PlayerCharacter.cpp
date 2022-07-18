// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "AnimInstanceBase.h"
#include "Kismet/KismetMathLibrary.h"
#include "ActorFactories/ActorFactory.h"
#include "Engine/World.h"
#include "Player/InputDataComponent.h"
#include "Player/CameraManager.h"


APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
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
	CameraArmLocation.Z = 15.f;
	FRotator CameraArmRotate = FRotator(340.0f, 0, .0f);
	CameraArmComponent->SetRelativeLocationAndRotation(CameraArmLocation, CameraArmRotate);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(CameraArmComponent);

	CamareManager->CreateDefaultSubobject<ACameraManager>(TEXT("CamaraManager"));

	InputDataComponent = CreateDefaultSubobject<UInputDataComponent>(TEXT("InputData"));
}

/* 입력 데이터 델리게이트 바인딩 함수들입니다. */
#pragma region InputData Binding Functions 

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputDataComponent->Setup(PlayerInputComponent);
}

void APlayerCharacter::MouseLeftPress()
{
	if (!IsValidInputDataComponent()) return;

	InputDataComponent->IsShoot(true);
}

void APlayerCharacter::MouseLeftRelease()
{
	if (!IsValidInputDataComponent()) return;

	InputDataComponent->IsShoot(false);
}

void APlayerCharacter::MouseRightPress()
{
	if (!IsValidInputDataComponent()) return;

	InputDataComponent->IsAim(true);
}

void APlayerCharacter::MouseRightRelease()
{
	if (!IsValidInputDataComponent()) return;

	InputDataComponent->IsAim(false);
}

void APlayerCharacter::MoveForward(float AxisValue)
{
	if (!IsValidInputDataComponent()) return;

	InputDataComponent->SetMoveDirectionX(AxisValue);
}

void APlayerCharacter::MoveRight(float AxisValue)
{
	if (!IsValidInputDataComponent()) return;

	InputDataComponent->SetMoveDirectionY(AxisValue);
}

void APlayerCharacter::Turn(float AxisValue)
{
	if (!IsValidInputDataComponent()) return;

	InputDataComponent->SetMouseLocationX(AxisValue);
}

void APlayerCharacter::LookUp(float AxisValue)
{
	if (!IsValidInputDataComponent()) return;

	InputDataComponent->SetMouseLocationY(AxisValue);
}

#pragma endregion

/* 변수의 유효함을 검증해주는 함수들입니다. */
#pragma region Variable Valid Functions 

bool APlayerCharacter::IsValidInputDataComponent() const
{
	return InputDataComponent != nullptr && InputDataComponent->IsValidLowLevelFast();
}

#pragma endregion


//void APlayerCharacter::Shoot()
//{
//	if (Projectile == nullptr || !Projectile->IsValidLowLevelFast() ||
//		Mesh == nullptr || !Mesh->IsValidLowLevelFast()) return;
//
//	FActorSpawnParameters SpawnParams;
//	SpawnParams.Owner = this;
//
//	GetWorld()->SpawnActor<AActor>(Projectile, Mesh->GetSocketLocation(GunMuzzleName), GetBaseAimRotation(), SpawnParams);
//}
// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "AnimInstanceBase.h"
#include "Kismet/KismetMathLibrary.h"
#include "Player/CameraManager.h"
#include "Player/InputDataComponent.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	// Component Init
	InputDataComponent = CreateDefaultSubobject<UInputDataComponent>(TEXT("InputData"));
	CameraArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	// Manager Init
	CamareManager = CreateDefaultSubobject<UCameraManager>(TEXT("CamaraManager"));
}

/* 입력 데이터 델리게이트 바인딩 함수들입니다. */
#pragma region InputData Binding Functions 

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (!IsValidInputDataComponent()) return;
	
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
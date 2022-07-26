// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/CameraManager.h"
#include "Player/PlayerCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Camera/CameraComponent.h"
#include "Player/InputDataComponent.h"

UCameraManager::UCameraManager()
{
	PlayerCharacter = Cast<APlayerCharacter>(GetOwner());
	if (!IsValidPlayerCharacter()) return;

	CameraArmComponent = PlayerCharacter->GetCameraArmComponent();
	if (!IsValidCameraArmComponent()) return;
	CameraArmComponent->SetupAttachment(PlayerCharacter->GetRootComponent());
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
	CameraArmLocation.Z = 40.f;
	FRotator CameraArmRotate = FRotator(340.0f, 0, .0f);
	CameraArmComponent->SetRelativeLocationAndRotation(CameraArmLocation, CameraArmRotate);

	CameraComponent = PlayerCharacter->GetCameraComponent();
	if (!IsValidCameraComponent()) return;
	CameraComponent->SetupAttachment(CameraArmComponent);

	InputDataComponent = PlayerCharacter->GetInputDataComponent();
	if (!IsValidInputDataComponent()) return;

	UE_LOG(LogTemp, Log, TEXT("CameraManager Init Complete"));
}

void UCameraManager::BeginPlay()
{
	if (!IsValidInputDataComponent()) return;

	InputDataComponent->OnInputMouseLocationX.AddDynamic(this, &UCameraManager::Turn);
	InputDataComponent->OnInputMouseLocationY.AddDynamic(this, &UCameraManager::LookUp);

	UE_LOG(LogTemp, Log, TEXT("CameraManager BeginPlay Complete"));
}

void UCameraManager::Turn()
{
	if (!IsValidPlayerCharacter() || !IsValidInputDataComponent()) return;

	PlayerCharacter->AddControllerYawInput(InputDataComponent->GetMouseLocation().X);
}

void UCameraManager::LookUp()
{
	if (!IsValidPlayerCharacter() || !IsValidCameraArmComponent() || !IsValidInputDataComponent()) return;

	FRotator rotation = CameraArmComponent->GetRelativeRotation();

	float pitch = UKismetMathLibrary::Clamp(rotation.Pitch - InputDataComponent->GetMouseLocation().Y, -60.f, 60.f);
	CameraArmComponent->SetRelativeRotation(FRotator(pitch, rotation.Yaw, rotation.Roll));
}

/* 변수의 유효함을 검증해주는 함수들입니다. */
#pragma region Variable Valid Functions 

bool UCameraManager::IsValidPlayerCharacter() const
{
	return PlayerCharacter != nullptr && PlayerCharacter->IsValidLowLevelFast();
}

bool UCameraManager::IsValidCameraArmComponent() const
{
	return CameraArmComponent != nullptr && CameraArmComponent->IsValidLowLevelFast();
}

bool UCameraManager::IsValidCameraComponent() const
{
	return CameraComponent != nullptr && CameraComponent->IsValidLowLevelFast();
}

bool UCameraManager::IsValidInputDataComponent() const
{
	return InputDataComponent != nullptr && InputDataComponent->IsValidLowLevelFast();
}

#pragma endregion

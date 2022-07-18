// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/CameraManager.h"
#include "Player/PlayerCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"

ACameraManager::ACameraManager()
{
	PlayerCharacter = Cast<APlayerCharacter>(GetOwner());
	if (!IsValidPlayerCharacter()) return;

	FTimerDelegate TimerDelegate;
	TimerDelegate.BindUFunction(this, FName("Initialize"));
	GetWorld()->GetTimerManager().SetTimerForNextTick(TimerDelegate);
}

void ACameraManager::Initialize()
{
	UKismetSystemLibrary::PrintString(GetWorld(), TEXT("Init !"));
}

void ACameraManager::Turn(float AxisValue)
{
	if (!IsValidPlayerCharacter()) return;

	PlayerCharacter->AddControllerYawInput(AxisValue);
}

void ACameraManager::LookUp(float AxisValue)
{
	if (!IsValidPlayerCharacter() || !IsValidCameraArmComponent()) return;

	FRotator rotation = CameraArmComponent->GetRelativeRotation();

	float pitch = UKismetMathLibrary::Clamp(rotation.Pitch - AxisValue, -60.f, 60.f);
	CameraArmComponent->SetRelativeRotation(FRotator(pitch, rotation.Yaw, rotation.Roll));
}

/* 변수의 유효함을 검증해주는 함수들입니다. */
#pragma region Variable Valid Functions 

bool ACameraManager::IsValidPlayerCharacter() const
{
	return PlayerCharacter != nullptr && PlayerCharacter->IsValidLowLevelFast();
}

bool ACameraManager::IsValidCameraArmComponent() const
{
	return CameraArmComponent != nullptr && CameraArmComponent->IsValidLowLevelFast();
}

#pragma endregion

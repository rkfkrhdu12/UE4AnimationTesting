// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "CameraManager.generated.h"

/**
 *
 */
UCLASS()
class ANIMTESTPROJECT_API ACameraManager : public APlayerCameraManager
{
	GENERATED_BODY()
public:
	ACameraManager();
private:
	void Initialize();
public:
	void Turn(float AxisValue);
	void LookUp(float AxisValue);

protected:
	class APlayerCharacter* PlayerCharacter;
	class UInputDataComponent* InputDataComponent;

	class USpringArmComponent* CameraArmComponent;
	class UCameraComponent* CameraComponent;

	FVector MousePosition = FVector::ZeroVector;
public:
	bool IsValidPlayerCharacter() const;
	bool IsValidCameraArmComponent() const;
};

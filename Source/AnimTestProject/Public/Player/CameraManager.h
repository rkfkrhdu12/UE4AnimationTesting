// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CameraManager.generated.h"

/**
 *
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ANIMTESTPROJECT_API UCameraManager : public UActorComponent
{
	GENERATED_BODY()
public:
	UCameraManager();
protected:
	virtual void BeginPlay() override;
public:
	UFUNCTION()
		void Turn();
	UFUNCTION()
		void LookUp();

protected:
	class APlayerCharacter* PlayerCharacter;
	class UInputDataComponent* InputDataComponent;

	class USpringArmComponent* CameraArmComponent;
	class UCameraComponent* CameraComponent;

	FVector MousePosition = FVector::ZeroVector;
public:
	bool IsValidPlayerCharacter() const;
	bool IsValidCameraArmComponent() const;
	bool IsValidCameraComponent() const;
	bool IsValidInputDataComponent() const;
};

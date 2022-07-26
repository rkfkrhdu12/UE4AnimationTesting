// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InputDataComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInputUpdate);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ANIMTESTPROJECT_API UInputDataComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UInputDataComponent();
protected:
	FVector MoveDirection = FVector::ZeroVector;
	FVector MouseLocation = FVector::ZeroVector;

	bool bIsAim = false;
	bool bIsShoot = false;
public:
	void Setup(class UInputComponent* inputComponent);

	FVector GetMoveDirection() const;
	void SetMoveDirection(const FVector& val);
	void SetMoveDirectionX(float val);
	void SetMoveDirectionY(float val);
	FOnInputUpdate OnInputMoveDirection;
	FOnInputUpdate OnInputMoveDirectionX;
	FOnInputUpdate OnInputMoveDirectionY;

	FVector GetMouseLocation() const;
	void SetMouseLocation(const FVector& val);
	void SetMouseLocationX(float val);
	void SetMouseLocationY(float val);
	FOnInputUpdate OnInputMouseLocation;
	FOnInputUpdate OnInputMouseLocationX;
	FOnInputUpdate OnInputMouseLocationY;

	bool IsAim() const;
	void IsAim(bool val);
	FOnInputUpdate OnInputAiming;

	bool IsShoot() const;
	void IsShoot(bool val);
	FOnInputUpdate OnInputShooting;
};

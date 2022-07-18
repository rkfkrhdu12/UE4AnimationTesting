// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InputDataComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInputUpdate);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ANIMTESTPROJECT_API UInputDataComponent : public UActorComponent
{
	GENERATED_BODY()
protected:
	FVector2D MoveDirection = FVector2D::ZeroVector;
	FVector2D MouseLocation = FVector2D::ZeroVector;

	bool bIsAim = false;
	bool bIsShoot = false;
public:
	void Setup(class UInputComponent* inputComponent);

	FVector2D GetMoveDirection() const;
	void SetMoveDirection(const FVector2D& val);
	FOnInputUpdate OnInputMoveDirection;
	void SetMoveDirectionX(float val);
	FOnInputUpdate OnInputMoveDirectionX;
	void SetMoveDirectionY(float val);
	FOnInputUpdate OnInputMoveDirectionY;

	FVector2D GetMouseLocation() const;
	void SetMouseLocation(const FVector2D& val);
	FOnInputUpdate OnInputMouseLocation;
	void SetMouseLocationX(float val);
	FOnInputUpdate OnInputMouseLocationX;
	void SetMouseLocationY(float val);
	FOnInputUpdate OnInputMouseLocationY;

	bool IsAim() const;
	void IsAim(bool val);
	FOnInputUpdate OnInputAiming;

	bool IsShoot() const;
	void IsShoot(bool val);
	FOnInputUpdate OnInputShooting;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InputDataComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ANIMTESTPROJECT_API UInputDataComponent : public UActorComponent
{
	GENERATED_BODY()
public:	
	UInputDataComponent();

protected:

	FVector2D MoveDirection = FVector2D::ZeroVector;
	FVector2D MouseLocation = FVector2D::ZeroVector;

	bool bIsAim = false;
	bool bIsShoot = false;
public:

	FVector2D GetMoveDirection() const;
	void SetMoveDirection(const FVector2D& val);
	void SetMoveDirectionX(float val);
	void SetMoveDirectionY(float val);

	FVector2D GetMouseLocation() const;
	void SetMouseLocation(const FVector2D& val);
	void SetMouseLocationX(float val);
	void SetMouseLocationY(float val);

	bool IsAim() const;
	void IsAim(bool val);

	bool IsShoot() const;
	void IsShoot(bool val);
};

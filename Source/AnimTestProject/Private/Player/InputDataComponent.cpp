// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/InputDataComponent.h"

// Sets default values for this component's properties
UInputDataComponent::UInputDataComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

/*        GetSet Function        */

// UInputDataComponent* UInputDataComponent::GetInstance()
// {
// 	return instance;
// }

FVector2D UInputDataComponent::GetMoveDirection() const
{
	return MoveDirection;
}

void UInputDataComponent::SetMoveDirection(const FVector2D& val)
{
	MoveDirection = val;
}

void UInputDataComponent::SetMoveDirectionX(float val)
{
	MoveDirection.X = val;
}

void UInputDataComponent::SetMoveDirectionY(float val)
{
	MoveDirection.Y = val;
}

bool UInputDataComponent::IsAim() const
{
	return bIsAim;
}

void UInputDataComponent::IsAim(bool val)
{
	bIsAim = val;
}

bool UInputDataComponent::IsShoot() const
{
	return bIsShoot;
}

void UInputDataComponent::IsShoot(bool val)
{
	bIsShoot = val;
}

FVector2D UInputDataComponent::GetMouseLocation() const
{
	return MouseLocation;
}

void UInputDataComponent::SetMouseLocation(const FVector2D& val)
{
	MouseLocation = val;
}

void UInputDataComponent::SetMouseLocationX(float val)
{
}

void UInputDataComponent::SetMouseLocationY(float val)
{
}

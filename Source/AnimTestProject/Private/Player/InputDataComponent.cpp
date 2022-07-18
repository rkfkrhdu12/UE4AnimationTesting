// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/InputDataComponent.h"
#include "Player/PlayerCharacter.h"
#include "Components/InputComponent.h"

void UInputDataComponent::Setup(UInputComponent* InputComponent)
{
	return;

	check(InputComponent);

	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetOwner());

	InputComponent->BindAxis("MoveForward", PlayerCharacter, &APlayerCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", PlayerCharacter, &APlayerCharacter::MoveRight);

	InputComponent->BindAxis("Turn", PlayerCharacter, &APlayerCharacter::Turn);
	InputComponent->BindAxis("LookUp", PlayerCharacter, &APlayerCharacter::LookUp);

	InputComponent->BindAction("Fire", IE_Pressed, PlayerCharacter, &APlayerCharacter::MouseLeftPress);
	InputComponent->BindAction("Fire", IE_Released, PlayerCharacter, &APlayerCharacter::MouseLeftRelease);
	InputComponent->BindAction("Fire2", IE_Pressed, PlayerCharacter, &APlayerCharacter::MouseRightPress);
	InputComponent->BindAction("Fire2", IE_Released, PlayerCharacter, &APlayerCharacter::MouseRightRelease);
}

/*       입력값들에 대한 Getter Setter 함수들 입니다.        */
#pragma region Get Set Functions

FVector2D UInputDataComponent::GetMoveDirection() const
{
	return MoveDirection;
}

void UInputDataComponent::SetMoveDirection(const FVector2D& val)
{
	MoveDirection = val;
	OnInputMoveDirection.Broadcast();
}

void UInputDataComponent::SetMoveDirectionX(float val)
{
	MoveDirection.X = val;
	OnInputMoveDirectionX.Broadcast();
}

void UInputDataComponent::SetMoveDirectionY(float val)
{
	MoveDirection.Y = val;
	OnInputMoveDirectionY.Broadcast();
}

bool UInputDataComponent::IsAim() const
{
	return bIsAim;
}

void UInputDataComponent::IsAim(bool val)
{
	bIsAim = val;
	OnInputAiming.Broadcast();
}

bool UInputDataComponent::IsShoot() const
{
	return bIsShoot;
}

void UInputDataComponent::IsShoot(bool val)
{
	bIsShoot = val;
	OnInputShooting.Broadcast();
}

FVector2D UInputDataComponent::GetMouseLocation() const
{
	return MouseLocation;
}

void UInputDataComponent::SetMouseLocation(const FVector2D& val)
{
	MouseLocation = val;
	OnInputMouseLocation.Broadcast();
}

void UInputDataComponent::SetMouseLocationX(float val)
{
	MouseLocation.X = val;
	OnInputMouseLocationX.Broadcast();
}

void UInputDataComponent::SetMouseLocationY(float val)
{
	MouseLocation.Y = val;
	OnInputMouseLocationY.Broadcast();
}

#pragma endregion

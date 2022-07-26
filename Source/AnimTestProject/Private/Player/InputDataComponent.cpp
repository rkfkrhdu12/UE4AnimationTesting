// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/InputDataComponent.h"
#include "Components/InputComponent.h"
#include "Player/PlayerCharacter.h"

UInputDataComponent::UInputDataComponent()
{
}

void UInputDataComponent::Setup(UInputComponent* InputComponent)
{
	check(InputComponent);

	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetOwner());
	if (PlayerCharacter == nullptr || !PlayerCharacter->IsValidLowLevelFast()) return;

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

FVector UInputDataComponent::GetMoveDirection() const
{
	return MoveDirection;
}

void UInputDataComponent::SetMoveDirection(const FVector& val)
{
	MoveDirection = val;
	if (OnInputMoveDirection.IsBound())
		OnInputMoveDirection.Broadcast();
}

void UInputDataComponent::SetMoveDirectionX(float val)
{
	MoveDirection.X = val;
	if (OnInputMoveDirectionX.IsBound())
		OnInputMoveDirectionX.Broadcast();
}

void UInputDataComponent::SetMoveDirectionY(float val)
{
	MoveDirection.Y = val;
	if (OnInputMoveDirectionY.IsBound())
		OnInputMoveDirectionY.Broadcast();
}

bool UInputDataComponent::IsAim() const
{
	return bIsAim;
}

void UInputDataComponent::IsAim(bool val)
{
	bIsAim = val;
	if (OnInputAiming.IsBound())
		OnInputAiming.Broadcast();
}

bool UInputDataComponent::IsShoot() const
{
	return bIsShoot;
}

void UInputDataComponent::IsShoot(bool val)
{
	bIsShoot = val;
	if (OnInputShooting.IsBound())
		OnInputShooting.Broadcast();
}

FVector UInputDataComponent::GetMouseLocation() const
{
	return MouseLocation;
}

void UInputDataComponent::SetMouseLocation(const FVector& val)
{
	MouseLocation = val;
	if (OnInputMouseLocation.IsBound())
		OnInputMouseLocation.Broadcast();
}

void UInputDataComponent::SetMouseLocationX(float val)
{
	MouseLocation.X = val;
	if (OnInputMouseLocationX.IsBound())
		OnInputMouseLocationX.Broadcast();
}

void UInputDataComponent::SetMouseLocationY(float val)
{
	MouseLocation.Y = val;
	if (OnInputMouseLocationY.IsBound())
		OnInputMouseLocationY.Broadcast();
}

#pragma endregion

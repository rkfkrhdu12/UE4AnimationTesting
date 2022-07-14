// Fill out your copyright notice in the Description page of Project Settings.

#include "ME_Testing/Monster6/Monster6Character.h"
#include "GameFramework/CharacterMovementComponent.h"

AMonster6Character::AMonster6Character()
{
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	CharacterMovement = GetCharacterMovement();
	CharacterMovement->bOrientRotationToMovement = true;
	CharacterMovement->RotationRate = FRotator(0.f, 600.f, 0.f);
}

void AMonster6Character::MoveForward(float AxisValue)
{
	if (CurLowerState != EMonster6LowerState::Idle) return;

	AddMovementInput(GetActorForwardVector(), AxisValue);
}

void AMonster6Character::MoveRight(float AxisValue)
{
	if (CurLowerState != EMonster6LowerState::Idle) return;

	AddMovementInput(GetActorRightVector(), AxisValue);
}

void AMonster6Character::Attack()
{
	if (CurUpperState == EMonster6UpperState::Attack) return;

	if (!IsValidAttackMontage()) return;

	ChangeUpperState(EMonster6UpperState::Attack);

	if (OnAttackAction.IsBound())
		OnAttackAction.Broadcast();

	PlayAnimMontage(AttackMontage);
}

void AMonster6Character::OnAnimBlendOut()
{
	if (CurUpperState == EMonster6UpperState::Attack)
	{
		ChangeUpperState(EMonster6UpperState::Idle);
	}
}

void AMonster6Character::ChangeUpperState(const EMonster6UpperState& state)
{
	CurUpperState = state;
	
	if (true)
	{
		CurLowerState = static_cast<EMonster6LowerState>(state);
	}
}

void AMonster6Character::ChangeLowerState(const EMonster6LowerState& state)
{
	CurLowerState = state;

	if (true)
	{
		CurUpperState = static_cast<EMonster6UpperState>(state);
	}
}

void AMonster6Character::LogPrint(const FString logString) const
{
	UE_LOG(LogTemp, Log, TEXT("%s"), *logString);
}

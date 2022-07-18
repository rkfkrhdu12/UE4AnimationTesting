// Fill out your copyright notice in the Description page of Project Settings.

#include "ME/Monster6/Monster6Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "ME/Monster6/Monster6Controller.h"
#include "Player/PlayerCharacter.h"


AMonster6Character::AMonster6Character()
{
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	Perception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception"));
	if (!IsValidPerception()) return;

	{ // Sight Init
		SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
		if (!IsValidSightConfig()) return;
		SightConfig->SightRadius = SightRadius;
		SightConfig->LoseSightRadius = LoseSightRadius;
		SightConfig->PeripheralVisionAngleDegrees = SightFOV;
		SightConfig->SetMaxAge(SightAge);

		SightConfig->DetectionByAffiliation.bDetectEnemies = true;
		SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
		SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

		Perception->SetDominantSense(*SightConfig->GetSenseImplementation());
		Perception->OnPerceptionUpdated.AddDynamic(this, &AMonster6Character::OnPawnDetected);
		Perception->ConfigureSense(*SightConfig);
	}

	AIController = Cast<AMonster6Controller>(GetController());
	if (IsValidAIController())
	{
		AIController->SetPerceptionComponent(*Perception);;
	}

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

void AMonster6Character::OnPawnDetected(const TArray<AActor*>& DetectedPawns)
{
	bIsFindPlayer = false;
	for (auto & var : DetectedPawns)
	{
		if (Cast<APlayerCharacter>(var))
		{
			if (PlayerCharacter == nullptr) PlayerCharacter = Cast<APlayerCharacter>(var);

			bIsFindPlayer = true;
		}
	}

	if (bIsFindPlayer)
		UKismetSystemLibrary::PrintString(GetWorld(), "Player found");
	else
		UKismetSystemLibrary::PrintString(GetWorld(), "Player not found");
}

bool AMonster6Character::IsValidPerception() const
{
	return Perception != nullptr && Perception->IsValidLowLevelFast();
}

bool AMonster6Character::IsValidSightConfig() const
{
	return SightConfig != nullptr && SightConfig->IsValidLowLevelFast();
}

bool AMonster6Character::IsValidAttackMontage() const
{
	return AttackMontage != nullptr && AttackMontage->IsValidLowLevelFast();
}

bool AMonster6Character::IsValidAIController() const
{
	return AIController != nullptr && AIController->IsValidLowLevelFast();
}

void AMonster6Character::LogPrint(const FString logString) const
{
	UE_LOG(LogTemp, Log, TEXT("%s"), *logString);
}

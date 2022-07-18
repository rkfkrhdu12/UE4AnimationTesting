// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "Monster6Character.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInputAxis, float, AxisValue);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAction);


UENUM(BlueprintType)
enum class EMonster6UpperState : uint8
{
	Idle,
	Attack,
	Last
};

UENUM(BlueprintType)
enum class EMonster6LowerState : uint8
{
	Idle,
	Attack,
	Last
};

UCLASS()
class ANIMTESTPROJECT_API AMonster6Character : public ACharacterBase
{
	GENERATED_BODY()
public:
	AMonster6Character();
protected:
	EMonster6UpperState CurUpperState = EMonster6UpperState::Idle;
	EMonster6LowerState CurLowerState = EMonster6LowerState::Idle;

	bool bIsFindPlayer = false;

public: /*                Behavior Function                */
	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
		FInputAxis OnMoveForward;
	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
		FInputAxis OnMoveRight;

	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
		FAction OnAttackAction;

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);

	void Attack();
public: /*                VariableControl Function                */
	void ChangeUpperState(const EMonster6UpperState& state);
	void ChangeLowerState(const EMonster6LowerState& state);

	UFUNCTION()
		void OnPawnDetected(const TArray<AActor*>& DetectedPawns);
protected: /*                Definition Variable                */
	class AMonster6Controller* AIController;

	class APlayerCharacter* PlayerCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UAIPerceptionComponent* Perception;

	class UAISenseConfig_Sight* SightConfig;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		float SightRadius = 500.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		float LoseSightRadius = SightRadius + 50.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		float SightAge = 3.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		float SightFOV = 90.f;

	class UCharacterMovementComponent* CharacterMovement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAnimMontage* AttackMontage;
public: /*                Get Set Function                */
	bool IsValidAttackMontage() const;
	bool IsValidAIController() const;
	bool IsValidPerception() const;
	bool IsValidSightConfig() const;

protected: /*                Debug Function                */
	void LogPrint(const FString logString) const;
};

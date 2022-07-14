// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Monster6Controller.generated.h"

UENUM(BlueprintType)
enum class EMonsterState : uint8
{
	Idle,
	Attack,
	Last
};

UCLASS()
class ANIMTESTPROJECT_API AMonster6Controller : public AAIController
{
	GENERATED_BODY()
public:
	AMonster6Controller();
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;

	virtual void Tick(float DeltaTime) override;

	virtual FRotator GetControlRotation() const override;
public:
	UFUNCTION()
		void OnPawnDetected(const TArray<AActor*>& DetectedPawns);

public:
	UPROPERTY(BlueprintReadWrite)
		EMonsterState CurState = EMonsterState::Idle;

	class AMonster6Character* Character;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UBehaviorTree* BehaviorTree;
	class UBehaviorTreeComponent* BehaviorTreeComponent;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//	class UBlackboardComponent* BlackBoard;

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
private:

public:
	bool IsValidPerception() const;
	bool IsValidSightConfig() const;
	bool IsValidCharacter() const;
	bool IsValidBehaviorTree() const;
	bool IsValidBehaviorTreeComponent() const;
	bool IsValidBlackBoard() const;

};

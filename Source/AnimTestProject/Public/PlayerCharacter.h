// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "PlayerCharacter.generated.h"

UENUM(BlueprintType)
enum class EPlayerState : uint8
{
	Idle		UMETA(DisplayName = "Idle"),
	Aim         UMETA(DisplayName = "Aim"),
	Fire		UMETA(DisplayName = "Fire"),
	Fire2		UMETA(DisplayName = "Fire2"),
	Last		UMETA(DisplayName = "None"),
};

UCLASS()
class ANIMTESTPROJECT_API APlayerCharacter : public ACharacterBase
{
	GENERATED_BODY()
public:
	APlayerCharacter();

protected:
	virtual void BeginPlay() override;
public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	void Fire();
	void Fire2();

public:
	void OnAnimBlendOut();
	void OnAnimNotify(const FName& notifyName);

public:
	UFUNCTION(BlueprintCallable)
		void MoveForward(float AxisValue);
	UFUNCTION(BlueprintCallable)
		void MoveRight(float AxisValue);

protected:
	UPROPERTY(BlueprintReadOnly)
		class USpringArmComponent* CameraArmComponent;
	UPROPERTY(BlueprintReadOnly)
		class UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		EPlayerState CurState = EPlayerState::Idle;
	EPlayerState PrevState = EPlayerState::Last;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AnimMontage")
		class UAnimMontage* FireAnimMontage = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AnimMontage")
		class UAnimMontage* Fire2AnimMontage = nullptr;

private:
	void ChangeState(EPlayerState nextState);
	void ReturnState();

	bool IsMoveable() const;

private: // DeBugging
	void PrintState();
};
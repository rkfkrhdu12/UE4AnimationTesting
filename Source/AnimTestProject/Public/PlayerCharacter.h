// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UENUM(BlueprintType)
enum class EPlayerState : uint8
{
	Idle		UMETA(DisplayName = "Idle"),
	Attack 	    UMETA(DisplayName = "Attack"),
	Fire		UMETA(DisplayName = "Fire"),
	Fire2		UMETA(DisplayName = "Fire2"),
	Last		UMETA(DisplayName = "None"),
};

UCLASS()
class ANIMTESTPROJECT_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()
public:
	APlayerCharacter();

protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
public:
	void Fire();
	void Fire2();

	void PlayMontage(UAnimMontage* montage);
public:
	UFUNCTION(BlueprintCallable)
		void OnAnimBlendOut(UAnimMontage* Montage, bool bInterrupted);
	UFUNCTION()
		void OnAnimNotify(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload);

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

	class USkeletalMeshComponent* Mesh = nullptr;
	class UAnimInstance* AnimInstance = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		EPlayerState CurState = EPlayerState::Idle;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AnimMontage")
		class UAnimMontage* FireAnimMontage = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AnimMontage")
		class UAnimMontage* Fire2AnimMontage = nullptr;
};
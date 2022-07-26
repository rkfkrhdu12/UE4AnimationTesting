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
public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	class UCameraManager* CamareManager = nullptr;

	UPROPERTY(BlueprintReadOnly)
		class USpringArmComponent* CameraArmComponent;
	UPROPERTY(BlueprintReadOnly)
		class UCameraComponent* CameraComponent;
	class UInputDataComponent* InputDataComponent = nullptr;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimMontage")
		class UAnimMontage* FireAnimMontage = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimMontage")
		class UAnimMontage* Fire2AnimMontage = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		FName GunMuzzleName = "Player_GunMuzzle";

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class AActor> Projectile;
public: 
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);

	void Turn(float AxisValue);
	void LookUp(float AxisValue);

	void MouseLeftPress();
	void MouseLeftRelease();
	void MouseRightPress();
	void MouseRightRelease();

	class USpringArmComponent* GetCameraArmComponent() const { return CameraArmComponent; }
	class UCameraComponent* GetCameraComponent() const { return CameraComponent; }
	class UInputDataComponent* GetInputDataComponent() const { return InputDataComponent; }
public:
	bool IsValidInputDataComponent() const;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "PlayerCharacter.generated.h"

UENUM(BlueprintType)
enum class EPlayerUpperState : uint8
{
	Idle		UMETA(DisplayName = "Idle"),
	Aim         UMETA(DisplayName = "Aim"),
	Fire		UMETA(DisplayName = "Fire"),
	Fire2		UMETA(DisplayName = "Fire2"),
	Last		UMETA(DisplayName = "None"),
};

UENUM(BlueprintType)
enum class EPlayerLowerState : uint8
{
	Idle		UMETA(DisplayName = "Idle"),
	Stop        UMETA(DisplayName = "Stop"),
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
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	void OnAnimBlendOut(UAnimMontage* Montage) override;
	void OnAnimNotify(const FName& notifyName) override;

public:
	UFUNCTION(BlueprintCallable)
		void MoveForward(float AxisValue);
	UFUNCTION(BlueprintCallable)
		void MoveRight(float AxisValue);

	void MouseLeftPress();
	void MouseRightPress();
	void MouseRightRelease();
protected:
	UPROPERTY(BlueprintReadOnly)
		class USpringArmComponent* CameraArmComponent;
	UPROPERTY(BlueprintReadOnly)
		class UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		EPlayerUpperState CurUpperState = EPlayerUpperState::Idle;
	EPlayerUpperState PrevUpperState = EPlayerUpperState::Last;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		EPlayerLowerState CurLowerState = EPlayerLowerState::Idle;
	EPlayerLowerState PrevLowerState = EPlayerLowerState::Last;

	bool bIsShootEnable = true;
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AnimMontage")
		class UAnimMontage* FireAnimMontage = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AnimMontage")
		class UAnimMontage* Fire2AnimMontage = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		FName GunMuzzleName = "Player_GunMuzzle";

	TArray<AActor*> DummyActors;
private:
	void ChangeUpperState(EPlayerUpperState nextState);
	void ReturnUpperState();

	void ChangeLowerState(EPlayerLowerState nextState);
	void ReturnLowerState();

	bool IsMoveable() const;

private: // DeBugging
	void PrintUpperState();
	void PrintLowerState();
};
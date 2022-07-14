// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ME_Testing/Monster6/Monster6Character.h"
#include "PlayerMonster6Character.generated.h"

/**
 * 
 */
UCLASS()
class ANIMTESTPROJECT_API APlayerMonster6Character : public AMonster6Character
{
	GENERATED_BODY()
public:
	APlayerMonster6Character();
public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected: /*                Default Variable                */
	UPROPERTY(BlueprintReadOnly)
		class USpringArmComponent* CameraArmComponent;
	UPROPERTY(BlueprintReadOnly)
		class UCameraComponent* CameraComponent;

public: /*                Get Set Function                */
	bool IsValidCameraArm() const;
	bool IsValidCamera() const;
};

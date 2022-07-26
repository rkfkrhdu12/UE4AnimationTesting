// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstanceBase.h"
#include "PlayerAnimInstance.generated.h"

/**
 *
 */
UCLASS()
class ANIMTESTPROJECT_API UPlayerAnimInstance : public UAnimInstanceBase
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool bIsAiming = false;

};

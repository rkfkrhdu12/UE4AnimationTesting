// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "PlayerCharacter.h"
#include "GAP_PlayerAnimNotify.generated.h"

/**
 * 
 */
UCLASS()
class ANIMTESTPROJECT_API UGAP_PlayerAnimNotify : public UAnimNotify
{
	GENERATED_BODY()
protected:
public:
	FString GetNotifyName_Implementation() const override;
public:
	virtual void BranchingPointNotify(FBranchingPointNotifyPayload& BranchingPointPayload) override;
};

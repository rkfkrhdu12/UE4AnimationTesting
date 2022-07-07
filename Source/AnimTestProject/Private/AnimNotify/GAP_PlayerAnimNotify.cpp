// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/GAP_PlayerAnimNotify.h"

FString UGAP_PlayerAnimNotify::GetNotifyName_Implementation() const
{
	return "None";
}

void UGAP_PlayerAnimNotify::BranchingPointNotify(FBranchingPointNotifyPayload& BranchingPointPayload)
{
	if (!this->IsValidLowLevelFast()) return;

}

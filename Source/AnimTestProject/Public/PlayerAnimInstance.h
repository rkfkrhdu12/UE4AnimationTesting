// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"


UCLASS()
class ANIMTESTPROJECT_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UPlayerAnimInstance();

	virtual void NativeBeginPlay() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	void UpdateSpeed();
	void UpdateDirection();

	void UpdateIKDisplacement();
	void UpdateIKGroundDistance(const FName& socketName, FRotator& rotate, float& ik);
	void UpdateFootIK();

	void FootDisplacementCheck(const FName& socketName, FHitResult& hitResult);
	void FootGroundDistance(const FName& socketName, FHitResult& hitResult);

	FVector GetSocketLocation(FName socketName) const;

	float GetDeltaTime() const { return GetWorld()->GetDeltaSeconds(); }
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float CurSpeed = 0.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float CurDirection = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float Displacement = 0.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FRotator RightFootRotate;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FRotator LeftFootRotate;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float RightFootIK;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float LeftFootIK;

private:
	class ACharacter* Character = nullptr;
	class USkeletalMeshComponent* CharacterMesh = nullptr;
	class UCharacterMovementComponent* CharacterMovement = nullptr;


	float MeshLocationOffsetZ = 90.f;

	FName RootName = "root";
	FName LeftFootName = "foot_l";
	FName RightFootName = "foot_r";
	FName LeftFootSocketName = "IK_Foot_L";
	FName RightFootSocketName = "IK_Foot_R";

	float IKInterpSpeed = 15.f;

	float DisplacementOffset = 10.f;

	float GroundCheckOffset = 60.f;

	const FVector FootSize = FVector(14.f, 5.0f, .1f);

	TArray<AActor*> DummyArray;
};

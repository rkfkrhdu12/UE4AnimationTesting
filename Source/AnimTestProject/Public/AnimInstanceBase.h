// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AnimInstanceBase.generated.h"


UCLASS()
class ANIMTESTPROJECT_API UAnimInstanceBase : public UAnimInstance
{
	GENERATED_BODY()
public:
	UAnimInstanceBase();

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

	float GetDeltaTime() const;
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool bIsMoving = false;
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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		FName RootName = "root";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		FName LeftFootSocketName = "IK_Foot_L";
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		FName RightFootSocketName = "IK_Foot_R";

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float IKInterpSpeed = 15.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float DisplacementOffset = 10.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float GroundCheckOffset = 60.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float LegLength = 80.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float footToGround = 10.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class ACharacter* Character = nullptr;
private:
	class USkeletalMeshComponent* CharacterMesh = nullptr;
	class UCharacterMovementComponent* CharacterMovement = nullptr;

	float MeshLocationOffsetZ = 90.f;

	TArray<AActor*> DummyArray;
};

// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstanceBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

UAnimInstanceBase::UAnimInstanceBase()
{
	
}

void UAnimInstanceBase::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	Character = Cast<ACharacter>(TryGetPawnOwner());

	UKismetSystemLibrary::PrintString(GetWorld(), TEXT("Init Character"));
	if (Character != nullptr && Character->IsValidLowLevelFast())
	{
		UKismetSystemLibrary::PrintString(GetWorld(), TEXT("Valid Character"));

		CharacterMesh = Character->GetMesh();
		if (CharacterMesh != nullptr && CharacterMesh->IsValidLowLevelFast())
		{
			MeshLocationOffsetZ = CharacterMesh->GetRelativeLocation().Z * -1.f;
		}

		CharacterMovement = Character->GetCharacterMovement();
	}
}

void UAnimInstanceBase::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Character == nullptr) return;

	UpdateSpeed();
	UpdateDirection();
	UpdatePitch();

	UpdateFootIK();
}

void UAnimInstanceBase::UpdateSpeed()
{
	if (Character == nullptr) return;

	CurSpeed = Character->GetVelocity().Size();
	bIsMoving = CurSpeed >= 10.f;
}

void UAnimInstanceBase::UpdateDirection()
{
	if (Character == nullptr) return;

	CurDirection = CalculateDirection(Character->GetVelocity(), Character->GetActorRotation());
}

void UAnimInstanceBase::UpdatePitch()
{
	if (Character == nullptr) return;

	float pitch = Character->GetBaseAimRotation().Pitch;

	CurPitch = (pitch >= 180) ?
		pitch - 360.f :
		pitch;
}

void UAnimInstanceBase::UpdateIKDisplacement()
{
	FHitResult leftFootHitResult;
	FHitResult rightFootHitResult;

	FootDisplacementCheck(LeftFootSocketName, leftFootHitResult);
	FootDisplacementCheck(RightFootSocketName, rightFootHitResult);

	if (!(leftFootHitResult.bBlockingHit || rightFootHitResult.bBlockingHit)) return;

	float leftFootDistance = leftFootHitResult.Distance;
	float rightFootDistance = rightFootHitResult.Distance;

	float distance = UKismetMathLibrary::SelectFloat(leftFootDistance, rightFootDistance, leftFootDistance >= rightFootDistance);
	distance = (distance - DisplacementOffset) * -1.f;

	Displacement = UKismetMathLibrary::FInterpTo(Displacement, distance, GetDeltaTime(), IKInterpSpeed);
}

void UAnimInstanceBase::UpdateIKGroundDistance(const FName& socketName, FRotator& rotate, float& ik)
{
	FHitResult hitResult;
	FootGroundDistance(socketName, hitResult);
	if (!hitResult.bBlockingHit) return;

	FVector hitNormal = hitResult.Normal;

	float roll = UKismetMathLibrary::DegAtan2(hitNormal.Y, hitNormal.Z);
	float pitch = UKismetMathLibrary::DegAtan2(hitNormal.X, hitNormal.Z) * -1.f;

	FRotator targetRotation = FRotator(pitch, 0.f, roll);

	rotate = UKismetMathLibrary::RInterpTo(rotate, targetRotation, GetDeltaTime(), IKInterpSpeed);

	float target = (hitResult.Distance - (GroundCheckOffset + footToGround)) / -45.f;

	ik = UKismetMathLibrary::FInterpTo(ik, target, GetDeltaTime(), IKInterpSpeed);
}

void UAnimInstanceBase::UpdateFootIK()
{
	if (Character == nullptr || CharacterMovement == nullptr) return;
	if (CharacterMovement->IsFalling()) return;

	UpdateIKDisplacement();

	UpdateIKGroundDistance(RightFootSocketName, RightFootRotate, RightFootIK);
	UpdateIKGroundDistance(LeftFootSocketName, LeftFootRotate, LeftFootIK);
}


void UAnimInstanceBase::FootDisplacementCheck(const FName& socketName, FHitResult& hitResult)
{
	if (CharacterMesh == nullptr || Character == nullptr) return;

	FVector startLocation = GetSocketLocation(socketName);
	startLocation.Z = CharacterMesh->GetComponentLocation().Z + DisplacementOffset;

	FVector endLocation = startLocation;
	endLocation.Z -= LegLength;

	UKismetSystemLibrary::LineTraceSingle(GetWorld(),
										  startLocation, endLocation,
										  ETraceTypeQuery::TraceTypeQuery1,
										  false,
										  DummyArray, EDrawDebugTrace::None, hitResult, true);
}

void UAnimInstanceBase::FootGroundDistance(const FName& socketName, FHitResult& hitResult)
{
	if (CharacterMesh == nullptr || Character == nullptr) return;

	FVector socketLocation = GetSocketLocation(socketName);
	FVector startLocation = FVector(socketLocation.X, socketLocation.Y, GetSocketLocation(RootName).Z);
	FVector endLocation = startLocation;
	startLocation.Z += GroundCheckOffset;
	endLocation.Z -= GroundCheckOffset;

	UKismetSystemLibrary::LineTraceSingle(GetWorld(),
										  startLocation, endLocation,
										  ETraceTypeQuery::TraceTypeQuery1,
										  false,
										  DummyArray, EDrawDebugTrace::None, hitResult, true);
}

FVector UAnimInstanceBase::GetSocketLocation(FName socketName) const
{
	if (CharacterMesh == nullptr) return FVector();

	return CharacterMesh->GetSocketLocation(socketName);
}

float UAnimInstanceBase::GetDeltaTime() const
{
	return GetWorld()->GetDeltaSeconds();
}

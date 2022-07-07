// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

UPlayerAnimInstance::UPlayerAnimInstance()
{
	
}

void UPlayerAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	Character = Cast<ACharacter>(TryGetPawnOwner());
	if (Character != nullptr && Character->IsValidLowLevelFast())
	{
		CharacterMesh = Character->GetMesh();
		if (CharacterMesh != nullptr && CharacterMesh->IsValidLowLevelFast())
		{
			MeshLocationOffsetZ = CharacterMesh->GetRelativeLocation().Z * -1.f;
		}

		CharacterMovement = Character->GetCharacterMovement();
	}
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Character == nullptr) return;

	UpdateSpeed();
	UpdateDirection();

	UpdateFootIK();
}

void UPlayerAnimInstance::UpdateSpeed()
{
	if (Character == nullptr) return;

	CurSpeed = Character->GetVelocity().Size();
}

void UPlayerAnimInstance::UpdateDirection()
{
	if (Character == nullptr) return;

	CurDirection = CalculateDirection(Character->GetVelocity(), Character->GetActorRotation());
}

void UPlayerAnimInstance::UpdateIKDisplacement()
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

void UPlayerAnimInstance::UpdateIKGroundDistance(const FName& socketName, FRotator& rotate, float& ik)
{
	FHitResult hitResult;
	FootGroundDistance(socketName, hitResult);
	if (!hitResult.bBlockingHit) return;

	FVector hitNormal = hitResult.Normal;

	float roll = UKismetMathLibrary::DegAtan2(hitNormal.Y, hitNormal.Z);
	float pitch = UKismetMathLibrary::DegAtan2(hitNormal.X, hitNormal.Z) * -1.f;

	FRotator targetRotation = FRotator(pitch, 0.f, roll);

	rotate = UKismetMathLibrary::RInterpTo(rotate, targetRotation, GetDeltaTime(), IKInterpSpeed);

	float target = (hitResult.Distance - (GroundCheckOffset + 10.f)) / -45.f;

	ik = UKismetMathLibrary::FInterpTo(ik, target, GetDeltaTime(), IKInterpSpeed);
}

void UPlayerAnimInstance::UpdateFootIK()
{
	if (Character == nullptr || CharacterMovement == nullptr) return;
	if (CharacterMovement->IsFalling()) return;

	UpdateIKDisplacement();

	UpdateIKGroundDistance(RightFootSocketName, RightFootRotate, RightFootIK);
	UpdateIKGroundDistance(LeftFootSocketName, LeftFootRotate, LeftFootIK);
}


void UPlayerAnimInstance::FootDisplacementCheck(const FName& socketName, FHitResult& hitResult)
{
	if (CharacterMesh == nullptr || Character == nullptr) return;

	FVector socketLocation = GetSocketLocation(socketName);

	FVector startLocation = socketLocation;
	startLocation.Z = CharacterMesh->GetComponentLocation().Z + DisplacementOffset;

	FVector endLocation = startLocation;
	endLocation.Z -= 200.f;

	UKismetSystemLibrary::LineTraceSingle(GetWorld(),
										  startLocation, endLocation,
										  ETraceTypeQuery::TraceTypeQuery1,
										  false,
										  DummyArray, EDrawDebugTrace::None, hitResult, true);
}

void UPlayerAnimInstance::FootGroundDistance(const FName& socketName, FHitResult& hitResult)
{
	if (CharacterMesh == nullptr || Character == nullptr) return;

	FVector socketLocation = GetSocketLocation(socketName);
	FVector startLocation = FVector(socketLocation.X, socketLocation.Y, GetSocketLocation(RootName).Z);
	FVector endLocation = startLocation;
	startLocation.Z += GroundCheckOffset;
	endLocation.Z -= GroundCheckOffset;

	FRotator rotation = FRotator(0.f, CharacterMesh->GetSocketRotation(socketName).Yaw, 0.f);

	UKismetSystemLibrary::LineTraceSingle(GetWorld(),
										  startLocation, endLocation,
										  ETraceTypeQuery::TraceTypeQuery1,
										  false,
										  DummyArray, EDrawDebugTrace::None, hitResult, true);

	//UKismetSystemLibrary::BoxTraceSingle(GetWorld(),
	//									 startLocation, endLocation, FootSize, rotation,
	//									 ETraceTypeQuery::TraceTypeQuery1,
	//									 false,
	//									 DummyArray, EDrawDebugTrace::None, hitResult, true);
}

FVector UPlayerAnimInstance::GetSocketLocation(FName socketName) const
{
	if (CharacterMesh == nullptr) return FVector();

	return CharacterMesh->GetSocketLocation(socketName);
}

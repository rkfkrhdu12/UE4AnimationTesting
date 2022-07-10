// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "AnimInstanceBase.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	CameraArmComponent->SetupAttachment(GetRootComponent());
	CameraArmComponent->TargetArmLength = 300.f;

	CameraArmComponent->bInheritPitch = false;
	CameraArmComponent->bInheritYaw = true;
	CameraArmComponent->bInheritRoll = false;

	CameraArmComponent->bEnableCameraLag = true;
	CameraArmComponent->CameraLagSpeed = 10.f;

	CameraArmComponent->bEnableCameraRotationLag = true;
	CameraArmComponent->CameraRotationLagSpeed = 30.f;

	FVector CameraArmLocation = FVector::ZeroVector;
	CameraArmLocation.X = -4.3f;
	CameraArmLocation.Z = 15.f;
	FRotator CameraArmRotate = FRotator(340.0f, 0, .0f);
	CameraArmComponent->SetRelativeLocationAndRotation(CameraArmLocation, CameraArmRotate);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(CameraArmComponent);

}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	OnAnimBlendOutDelegate.AddDynamic(this, &APlayerCharacter::OnAnimBlendOut);
	OnAnimNotifyDelegate.AddDynamic(this, &APlayerCharacter::OnAnimNotify);
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APlayerCharacter::Fire);
	PlayerInputComponent->BindAction("Fire2", IE_Pressed, this, &APlayerCharacter::Fire2);
}

void APlayerCharacter::Fire()
{
	ChangeState(EPlayerState::Fire);

	PlayAnimMontage(FireAnimMontage);
}

void APlayerCharacter::Fire2()
{
	ChangeState(EPlayerState::Fire2);

	PlayAnimMontage(Fire2AnimMontage);
}

void APlayerCharacter::OnAnimBlendOut()
{
	PrintString("OnAnimBlendOut");

	ReturnState();
}

void APlayerCharacter::OnAnimNotify(const FName& NotifyName)
{
}

void APlayerCharacter::MoveForward(float AxisValue)
{
	if (!IsMoveable()) return;

	AddMovementInput(GetActorForwardVector(), AxisValue);
}

void APlayerCharacter::MoveRight(float AxisValue)
{
	if (!IsMoveable()) return;

	AddMovementInput(GetActorRightVector(), AxisValue);
}

void APlayerCharacter::ChangeState(EPlayerState nextState)
{
	if (CurState == nextState) return;

	PrevState = CurState;
	CurState = nextState;

	PrintState();
}

void APlayerCharacter::ReturnState()
{
	if (PrevState == EPlayerState::Last) return;
	
	CurState = PrevState;
	PrevState = EPlayerState::Last;
	
	PrintState();
}

bool APlayerCharacter::IsMoveable() const
{
	return CurState != EPlayerState::Fire2;
}

void APlayerCharacter::PrintState()
{
	const UEnum* enumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EPlayerState"), true);
	if (!enumPtr) return;

	UKismetSystemLibrary::PrintString(GetWorld(), enumPtr->GetNameStringByIndex((int32)CurState));
}


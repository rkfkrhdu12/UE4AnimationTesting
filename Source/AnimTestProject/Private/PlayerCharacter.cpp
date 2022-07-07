// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetSystemLibrary.h"

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

	Mesh = GetMesh();
	if (Mesh != nullptr && Mesh->IsValidLowLevelFast()) AnimInstance = Mesh->GetAnimInstance();
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (Mesh == nullptr) Mesh = GetMesh();

	if (AnimInstance == nullptr && Mesh != nullptr) AnimInstance = Mesh->GetAnimInstance();
	if (AnimInstance != nullptr && AnimInstance->IsValidLowLevelFast())
	{
		AnimInstance->OnMontageBlendingOut.AddDynamic(this, &APlayerCharacter::OnAnimBlendOut);
		AnimInstance->OnPlayMontageNotifyBegin.AddDynamic(this, &APlayerCharacter::OnAnimNotify);
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APlayerCharacter::Fire);
	PlayerInputComponent->BindAction("Fire2", IE_Pressed, this, &APlayerCharacter::Fire2);
}

void APlayerCharacter::Fire()
{
	CurState = EPlayerState::Attack;

	PlayMontage(FireAnimMontage);
}

void APlayerCharacter::Fire2()
{
	CurState = EPlayerState::Attack;

	PlayMontage(Fire2AnimMontage);
}

void APlayerCharacter::PlayMontage(UAnimMontage* montage)
{
	if (montage == nullptr) return;

	PlayAnimMontage(montage);
}

void APlayerCharacter::OnAnimBlendOut(UAnimMontage* Montage, bool bInterrupted)
{
	CurState = EPlayerState::Idle;
}

void APlayerCharacter::OnAnimNotify(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload)
{
	if (NotifyName == "Fire")
		CurState = EPlayerState::Fire;

	if (NotifyName == "Fire2")
		CurState = EPlayerState::Fire2;
}

void APlayerCharacter::MoveForward(float AxisValue)
{
	if (CurState != EPlayerState::Idle) return;

	AddMovementInput(GetActorForwardVector(), AxisValue);
}

void APlayerCharacter::MoveRight(float AxisValue)
{
	if (CurState != EPlayerState::Idle) return;

	AddMovementInput(GetActorRightVector(), AxisValue);
}


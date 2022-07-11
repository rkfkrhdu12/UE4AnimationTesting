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
	CameraArmLocation.Y = 10.f;
	CameraArmLocation.Z = 15.f;
	FRotator CameraArmRotate = FRotator(340.0f, 0, .0f);
	CameraArmComponent->SetRelativeLocationAndRotation(CameraArmLocation, CameraArmRotate);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(CameraArmComponent);
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bIsShootEnable)
	{
		FHitResult hitresult;
		FVector GunMuzzleLocation = Mesh->GetSocketLocation(GunMuzzleName);
		UKismetSystemLibrary::LineTraceSingle(GetWorld(),
											  GunMuzzleLocation,
											  GunMuzzleLocation + GetActorForwardVector() * 500.f,
											  ETraceTypeQuery::TraceTypeQuery1,
											  false,
											  DummyActors,
											  EDrawDebugTrace::ForOneFrame,
											  hitresult,
											  true,
											  FLinearColor::Red,
											  FLinearColor::Green,
											  .1f);


	}
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APlayerCharacter::MouseLeftPress);
	PlayerInputComponent->BindAction("Fire2", IE_Pressed, this, &APlayerCharacter::MouseRightPress);
	PlayerInputComponent->BindAction("Fire2", IE_Released, this, &APlayerCharacter::MouseRightRelease);
}

void APlayerCharacter::MouseLeftPress()
{
	if (CurUpperState == EPlayerUpperState::Aim)
	{
		ChangeUpperState(EPlayerUpperState::Fire2);

		PlayAnimMontage(Fire2AnimMontage);
	}
	else
	{
		ChangeUpperState(EPlayerUpperState::Fire);

		PlayAnimMontage(FireAnimMontage);
	}
}

void APlayerCharacter::MouseRightPress()
{
	ChangeUpperState(EPlayerUpperState::Aim);
}

void APlayerCharacter::MouseRightRelease()
{
	ChangeUpperState(EPlayerUpperState::Idle);
}

void APlayerCharacter::OnAnimBlendOut(UAnimMontage* Montage)
{
	if (Montage->IsValidSlot("DefaultSlot"))
	{
		ReturnLowerState();
	}
	else
	{
		ReturnUpperState();
	}
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

void APlayerCharacter::ChangeUpperState(EPlayerUpperState nextState)
{
	if (CurUpperState == nextState) return;

	PrevUpperState = CurUpperState;
	CurUpperState = nextState;

	PrintUpperState();
}

void APlayerCharacter::ReturnUpperState()
{
	if (PrevUpperState == EPlayerUpperState::Last) return;

	CurUpperState = PrevUpperState;
	PrevUpperState = EPlayerUpperState::Last;

	PrintUpperState();
}

void APlayerCharacter::ChangeLowerState(EPlayerLowerState nextState)
{
	if (CurLowerState == nextState) return;

	PrevLowerState = CurLowerState;
	CurLowerState = nextState;

	PrintUpperState();
}

void APlayerCharacter::ReturnLowerState()
{
	if (PrevLowerState == EPlayerLowerState::Last) return;

	CurLowerState = PrevLowerState;
	PrevLowerState = EPlayerLowerState::Last;

	PrintLowerState();
}

bool APlayerCharacter::IsMoveable() const
{
	return CurLowerState == EPlayerLowerState::Idle && CurUpperState != EPlayerUpperState::Fire2;
}

void APlayerCharacter::PrintUpperState()
{
	const UEnum* enumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EPlayerUpperState"), true);
	if (enumPtr == nullptr) return;

	UKismetSystemLibrary::PrintString(GetWorld(), enumPtr->GetNameStringByIndex((int32)CurUpperState));
}

void APlayerCharacter::PrintLowerState()
{
	const UEnum* enumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EPlayerLowerState"), true);
	if (enumPtr == nullptr) return;

	UKismetSystemLibrary::PrintString(GetWorld(), enumPtr->GetNameStringByIndex((int32)CurLowerState));
}

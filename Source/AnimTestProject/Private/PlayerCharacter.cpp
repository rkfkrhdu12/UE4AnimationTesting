// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "AnimInstanceBase.h"
#include "Kismet/KismetMathLibrary.h"
#include "ActorFactories/ActorFactory.h"
#include "Engine/World.h"

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

		FVector AimDirection = UKismetMathLibrary::GetForwardVector(GetBaseAimRotation());

		UKismetSystemLibrary::LineTraceSingle(GetWorld(),
											  GunMuzzleLocation,
											  GunMuzzleLocation + AimDirection * 500.f,
											  ETraceTypeQuery::TraceTypeQuery1,
											  false,
											  DummyActors,
											  EDrawDebugTrace::ForDuration,
											  hitresult,
											  true,
											  FLinearColor::Red,
											  FLinearColor::Green,
											  .05f);

		if (bIsShoot)
		{
			if (CurUpperState == EPlayerUpperState::Fire2 || CurUpperState == EPlayerUpperState::Fire) return;

			if (CurUpperState == EPlayerUpperState::Aim)
			{
				ChangeUpperState(EPlayerUpperState::Fire2);

				Shoot();

				PlayAnimMontage(Fire2AnimMontage);
			}
			else
			{
				ChangeUpperState(EPlayerUpperState::Fire);

				Shoot();

				PlayAnimMontage(FireAnimMontage);
			}
		}
	}
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APlayerCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::LookUp);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APlayerCharacter::MouseLeftPress);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &APlayerCharacter::MouseLeftRelease);
	PlayerInputComponent->BindAction("Fire2", IE_Pressed, this, &APlayerCharacter::MouseRightPress);
	PlayerInputComponent->BindAction("Fire2", IE_Released, this, &APlayerCharacter::MouseRightRelease);
}

void APlayerCharacter::MouseLeftPress()
{
	bIsShoot = true;
}

void APlayerCharacter::MouseLeftRelease()
{
	bIsShoot = false;
}

void APlayerCharacter::MouseRightPress()
{
	bIsAiming = true;

	ChangeUpperState(EPlayerUpperState::Aim);
}

void APlayerCharacter::MouseRightRelease()
{
	bIsAiming = false;

	ChangeUpperState(EPlayerUpperState::Idle);
}

void APlayerCharacter::Shoot()
{
	if (Projectile == nullptr || !Projectile->IsValidLowLevelFast() ||
		Mesh == nullptr || !Mesh->IsValidLowLevelFast()) return;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;

	GetWorld()->SpawnActor<AActor>(Projectile, Mesh->GetSocketLocation(GunMuzzleName), GetBaseAimRotation(), SpawnParams);
}

void APlayerCharacter::OnAnimBlendOut()
{
	PrintString("BlendOut");
}

void APlayerCharacter::OnUpperAnimBlendOut()
{
	PrintString("ReturnUpperState");
	ReturnUpperState();
}

void APlayerCharacter::OnLowerAnimBlendOut()
{
	PrintString("ReturnLowerState");
	ReturnLowerState();
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

void APlayerCharacter::Turn(float AxisValue)
{
	AddControllerYawInput(AxisValue);
}

void APlayerCharacter::LookUp(float AxisValue)
{
	if (CameraArmComponent == nullptr || !CameraArmComponent->IsValidLowLevelFast()) return;

	FRotator rotation = CameraArmComponent->GetRelativeRotation();

	float pitch = UKismetMathLibrary::Clamp(rotation.Pitch - AxisValue, -60.f, 60.f);
	CameraArmComponent->SetRelativeRotation(FRotator(pitch, rotation.Yaw, rotation.Roll));
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

	PrintLowerState();
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

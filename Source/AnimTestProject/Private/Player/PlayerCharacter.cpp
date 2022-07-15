// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "AnimInstanceBase.h"
#include "Kismet/KismetMathLibrary.h"
#include "ActorFactories/ActorFactory.h"
#include "Engine/World.h"
#include "Player/InputDataComponent.h"

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

	InputDataComponent = CreateDefaultSubobject<UInputDataComponent>(TEXT("InputData"));
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// if (bIsShootEnable)
	{
		//FHitResult hitresult;
		//FVector GunMuzzleLocation = Mesh->GetSocketLocation(GunMuzzleName);

		//FVector AimDirection = UKismetMathLibrary::GetForwardVector(GetBaseAimRotation());

		//UKismetSystemLibrary::LineTraceSingle(GetWorld(),
		//									  GunMuzzleLocation,
		//									  GunMuzzleLocation + AimDirection * 500.f,
		//									  ETraceTypeQuery::TraceTypeQuery1,
		//									  false,
		//									  DummyActors,
		//									  EDrawDebugTrace::ForDuration,
		//									  hitresult,
		//									  true,
		//									  FLinearColor::Red,
		//									  FLinearColor::Green,
		//									  .05f);

		//if (bIsShoot)
		//{
		//	if (CurUpperState == EPlayerUpperState::Fire2 || CurUpperState == EPlayerUpperState::Fire) return;

		//	if (CurUpperState == EPlayerUpperState::Aim)
		//	{
		//		ChangeUpperState(EPlayerUpperState::Fire2);

		//		Shoot();

		//		PlayAnimMontage(Fire2AnimMontage);
		//	}
		//	else
		//	{
		//		ChangeUpperState(EPlayerUpperState::Fire);

		//		Shoot();

		//		PlayAnimMontage(FireAnimMontage);
		//	}
		//}
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
}

void APlayerCharacter::MouseLeftRelease()
{
}

void APlayerCharacter::MouseRightPress()
{
	// bIsAiming = true;

	// ChangeUpperState(EPlayerUpperState::Aim);
}

void APlayerCharacter::MouseRightRelease()
{
	// bIsAiming = false;

	// ChangeUpperState(EPlayerUpperState::Idle);
}
bool APlayerCharacter::IsValidInputDataComponent() const
{
	return InputDataComponent != nullptr && InputDataComponent->IsValidLowLevelFast();
}
//
//void APlayerCharacter::Shoot()
//{
//	if (Projectile == nullptr || !Projectile->IsValidLowLevelFast() ||
//		Mesh == nullptr || !Mesh->IsValidLowLevelFast()) return;
//
//	FActorSpawnParameters SpawnParams;
//	SpawnParams.Owner = this;
//
//	GetWorld()->SpawnActor<AActor>(Projectile, Mesh->GetSocketLocation(GunMuzzleName), GetBaseAimRotation(), SpawnParams);
//}

void APlayerCharacter::MoveForward(float AxisValue)
{
	if (!IsValidInputDataComponent()) return;

	InputDataComponent->SetMoveDirectionX(AxisValue);
}

void APlayerCharacter::MoveRight(float AxisValue)
{
	if (!IsValidInputDataComponent()) return;

	InputDataComponent->SetMoveDirectionY(AxisValue);
}

void APlayerCharacter::Turn(float AxisValue)
{
	if (!IsValidInputDataComponent()) return;

	InputDataComponent->SetMouseLocationX(AxisValue);

	// AddControllerYawInput(AxisValue);
}

void APlayerCharacter::LookUp(float AxisValue)
{
	if (!IsValidInputDataComponent()) return;

	InputDataComponent->SetMouseLocationY(AxisValue);

	// if (CameraArmComponent == nullptr || !CameraArmComponent->IsValidLowLevelFast()) return;
	// 
	// FRotator rotation = CameraArmComponent->GetRelativeRotation();
	// 
	// float pitch = UKismetMathLibrary::Clamp(rotation.Pitch - AxisValue, -60.f, 60.f);
	// CameraArmComponent->SetRelativeRotation(FRotator(pitch, rotation.Yaw, rotation.Roll));
}
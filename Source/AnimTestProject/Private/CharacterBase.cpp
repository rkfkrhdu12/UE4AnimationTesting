#include "CharacterBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "AnimInstanceBase.h"

ACharacterBase::ACharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();

	Mesh = GetMesh();
	if (Mesh != nullptr && Mesh->IsValidLowLevelFast())
		AnimInstance = Cast<UAnimInstanceBase>(Mesh->GetAnimInstance());

	if (AnimInstance != nullptr && AnimInstance->IsValidLowLevelFast())
	{
		AnimInstance->OnMontageBlendingOut.AddDynamic(this, &ACharacterBase::OnAnimBlendOutA);
		AnimInstance->OnPlayMontageNotifyBegin.AddDynamic(this, &ACharacterBase::OnAnimNotifyA);
	}
}

void ACharacterBase::OnAnimBlendOutA(UAnimMontage* Montage, bool bInterrupted)
{
	PrintString("BlendOut");

	OnAnimBlendOutDelegate.Broadcast();
}

void ACharacterBase::OnAnimNotifyA(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload)
{
	OnAnimNotifyDelegate.Broadcast(NotifyName);
}

void ACharacterBase::PrintString(const FString& printString)
{
	UKismetSystemLibrary::PrintString(GetWorld(), printString);
}

#include "CharacterBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "AnimInstanceBase.h"
#include "CharacterBehaviorManager.h"

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
	OnAnimBlendOutDelegate.Broadcast();

	//OnAnimBlendOut();
	//if (Montage->IsValidSlot("DefaultSlot"))
	//{
	//	OnLowerAnimBlendOut();
	//}
	//else
	//{
	//	OnUpperAnimBlendOut();
	//}
}

void ACharacterBase::OnAnimNotifyA(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload)
{
	OnAnimNotifyDelegate.Broadcast(NotifyName);

	OnAnimNotify(NotifyName);
}

void ACharacterBase::OnAnimNotify(const FName& NotifyName)
{
}

void ACharacterBase::ChangeState(const uint8& nextState)
{
	if (!IsValidBehaviorManager()) return;
	
	BehaviorManager->ChangeState(nextState);
}

void ACharacterBase::ReturnState()
{
	if (!IsValidBehaviorManager()) return;

	BehaviorManager->ReturnState();
}

bool ACharacterBase::IsValidBehaviorManager() const
{
	return BehaviorManager != nullptr && BehaviorManager->IsValid();
}

void ACharacterBase::PrintString(const FString& printString)
{
	UKismetSystemLibrary::PrintString(GetWorld(), printString);
}

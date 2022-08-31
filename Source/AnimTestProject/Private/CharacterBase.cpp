#include "CharacterBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "AnimInstanceBase.h"
#include "CharacterBehaviorStateManager.h"

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
}

void ACharacterBase::ChangeState(const uint8& nextState)
{
	if (!IsValidBehaviorManager()) return;
	
	StateManager->ChangeState(nextState);
	OnChangeStateDelegate.Broadcast();
}

void ACharacterBase::ReturnState()
{
	if (!IsValidBehaviorManager()) return;

	StateManager->ReturnState();
	OnChangeStateDelegate.Broadcast();
}

bool ACharacterBase::IsValidBehaviorManager() const
{
	return StateManager != nullptr;
}

void ACharacterBase::PrintString(const FString& printString)
{
	UKismetSystemLibrary::PrintString(GetWorld(), printString);
}

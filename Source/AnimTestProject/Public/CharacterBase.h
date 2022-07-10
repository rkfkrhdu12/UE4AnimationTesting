#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAnimBlendOut);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAnimNotify, const FName&, NotifyName);

UCLASS()
class ANIMTESTPROJECT_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()
public:
	ACharacterBase();

protected:
	virtual void BeginPlay() override;
public:
	FAnimBlendOut OnAnimBlendOutDelegate;
	FAnimNotify OnAnimNotifyDelegate;

	UFUNCTION()
		virtual void OnAnimBlendOutA(UAnimMontage* Montage, bool bInterrupted);
	UFUNCTION()
		virtual void OnAnimNotifyA(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload);
	
protected:
	class USkeletalMeshComponent* Mesh = nullptr;
	class UAnimInstanceBase* AnimInstance = nullptr;

protected:
	void PrintString(const FString& printString);
};


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
	UFUNCTION()
		virtual void OnAnimNotify(const FName& NotifyName);

	void OnChangeState() {}
public:
	void ChangeState(const uint8& nextState);
	void ReturnState();

protected:
	class USkeletalMeshComponent* Mesh = nullptr;
	class UAnimInstanceBase* AnimInstance = nullptr;
	class UCharacterBehaviorManager* BehaviorManager = nullptr;

	uint8 CurState = static_cast<uint8>(0);
public:
	bool IsValidBehaviorManager() const;

protected: /*         Debug         */
	void PrintString(const FString& printString);
};


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCharacterEvent);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAnimBlendOut);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAnimNotify, const FName&, NotifyName);


UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	Idle		UMETA(DisplayName = "Idle"),
	Move		UMETA(DisplayName = "Move"),
	Last		UMETA(DisplayName = "None"),
};

UCLASS()
class ANIMTESTPROJECT_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()
public:
	ACharacterBase();

protected:
	virtual void BeginPlay() override;
public:
	FOnCharacterEvent OnChangeStateDelegate;

	FOnAnimBlendOut OnAnimBlendOutDelegate;
	FOnAnimNotify OnAnimNotifyDelegate;

	UFUNCTION()
		virtual void OnAnimBlendOutA(UAnimMontage* Montage, bool bInterrupted);
	UFUNCTION()
		virtual void OnAnimNotifyA(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload);
public:
	void ChangeState(const uint8& nextState);
	void ReturnState();

protected:
	class USkeletalMeshComponent* Mesh = nullptr;
	class UAnimInstanceBase* AnimInstance = nullptr;
	class UCharacterBehaviorStateManager* StateManager = nullptr;

	uint8 CurState = static_cast<uint8>(0);
public:
	bool IsValidBehaviorManager() const;

protected: /*         Debug         */
	void PrintString(const FString& printString);
};


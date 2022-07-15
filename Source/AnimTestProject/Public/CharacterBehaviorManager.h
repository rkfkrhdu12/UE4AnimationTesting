#pragma once

#include "CharacterBehaviorManager.generated.h"

UENUM(BlueprintType)
enum class ECharacterUpperState : uint8
{
	Idle		UMETA(DisplayName = "Idle"),
	Last		UMETA(DisplayName = "None"),
};

UENUM(BlueprintType)
enum class ECharacterLowerState : uint8
{
	Idle		UMETA(DisplayName = "Idle"),
	Stop        UMETA(DisplayName = "Stop"),
	Last		UMETA(DisplayName = "None"),
};

class UCharacterBehaviorManager
{
public:
	UCharacterBehaviorManager();

	void ChangeState(const uint8 state);
	void ReturnState();

private:
	uint8 CurUpperState = static_cast<uint8>(0);
	uint8 PrevUpperState = static_cast<uint8>(99);

	uint8 CurLowerState = static_cast<uint8>(0);
	uint8 PrevLowerState = static_cast<uint8>(99);

public:
	bool IsValid() const;
};
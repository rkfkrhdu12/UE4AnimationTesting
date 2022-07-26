#include "CharacterBehaviorManager.h"

UCharacterBehaviorManager::UCharacterBehaviorManager()
{
}

void UCharacterBehaviorManager::ChangeState(const uint8 state)
{
	if (state == CurState) return;

	PrevState = CurState;
	CurState = state;

	// Update State
}

void UCharacterBehaviorManager::ReturnState()
{
	if (static_cast<uint8>(99) == PrevState) ChangeState(static_cast<uint8>(0));

	CurState = PrevState;
	PrevState = static_cast<uint8>(99);

	// Update State
}
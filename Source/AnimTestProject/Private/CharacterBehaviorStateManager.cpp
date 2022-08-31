#include "CharacterBehaviorStateManager.h"

UCharacterBehaviorStateManager::UCharacterBehaviorStateManager()
{
}

void UCharacterBehaviorStateManager::ChangeState(const uint8 state)
{
	if (state == CurState) return;

	PrevState = CurState;
	CurState = state;

	// Update State
}

void UCharacterBehaviorStateManager::ReturnState()
{
	if (static_cast<uint8>(99) == PrevState) ChangeState(static_cast<uint8>(0));

	CurState = PrevState;
	PrevState = static_cast<uint8>(99);

	// Update State
}
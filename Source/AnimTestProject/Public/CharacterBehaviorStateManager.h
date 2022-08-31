#pragma once

class UCharacterBehaviorStateManager
{
public:
	UCharacterBehaviorStateManager();

	void ChangeState(const uint8 state);
	void ReturnState();

private:
	uint8 CurState = static_cast<uint8>(0);
	uint8 PrevState = static_cast<uint8>(99);
};
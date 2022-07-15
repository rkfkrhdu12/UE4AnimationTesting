// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerMonster6Controller.generated.h"

/**
 *
 */
UCLASS()
class ANIMTESTPROJECT_API APlayerMonster6Controller : public APlayerController
{
	GENERATED_BODY()
public:
	APlayerMonster6Controller();

	virtual void BeginPlay() override;
public:

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class APlayerMonster6Character* Monster6Character;

public:
	bool IsValidCharacter() const;
protected:
	void LogPrint(const FString logString) const;
};

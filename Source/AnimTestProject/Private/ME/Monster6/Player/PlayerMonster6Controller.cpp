// Fill out your copyright notice in the Description page of Project Settings.


#include "ME/Monster6/Player/PlayerMonster6Controller.h"
#include "Kismet/KismetSystemLibrary.h"

#include "ME/Monster6/Player/PlayerMonster6Character.h"
APlayerMonster6Controller::APlayerMonster6Controller()
{
	PrimaryActorTick.bCanEverTick = true;

}

void APlayerMonster6Controller::BeginPlay()
{
	Super::BeginPlay();

	Monster6Character = Cast<APlayerMonster6Character>(GetCharacter());
	if (!IsValidCharacter()) { LogPrint("AMonster6Character : Character is Null"); return; }
}

bool APlayerMonster6Controller::IsValidCharacter() const
{
	return Monster6Character != nullptr && Monster6Character->IsValidLowLevelFast();
}

void APlayerMonster6Controller::LogPrint(const FString logString) const
{
	UE_LOG(LogTemp, Log, TEXT("%s"), *logString);
}

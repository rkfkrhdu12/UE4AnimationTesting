// Fill out your copyright notice in the Description page of Project Settings.


#include "ME/Monster6/Monster6Controller.h"
#include "ME/Monster6/Monster6Character.h"
#include "Kismet/KismetSystemLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

AMonster6Controller::AMonster6Controller()
{
	PrimaryActorTick.bCanEverTick = true;

	this->bAttachToPawn = false;
	
	if (IsValidBehaviorTree())
	{
		BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BT Component"));
		Blackboard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BB Component"));
	}
}

void AMonster6Controller::BeginPlay()
{
	Super::BeginPlay();

	Character = Cast<AMonster6Character>(GetPawn());
	if (!IsValidCharacter()) return;

	if (IsValidBehaviorTree() && IsValidBehaviorTreeComponent())
	{
		RunBehaviorTree(BehaviorTree);
		BehaviorTreeComponent->StartTree(*BehaviorTree);
	}
}

void AMonster6Controller::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (IsValidBehaviorTree() && IsValidBlackBoard())
	{
		Blackboard->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	}
}

void AMonster6Controller::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FRotator AMonster6Controller::GetControlRotation() const
{
	return IsValidCharacter() ? 
		FRotator(0.f, Character->GetActorRotation().Yaw,0.f) :
		FRotator::ZeroRotator;
}


bool AMonster6Controller::IsValidCharacter() const
{
	return Character != nullptr && Character->IsValidLowLevelFast();
}

bool AMonster6Controller::IsValidBehaviorTree() const
{
	return BehaviorTree != nullptr && BehaviorTree->IsValidLowLevelFast();
}

bool AMonster6Controller::IsValidBehaviorTreeComponent() const
{
	return BehaviorTreeComponent != nullptr && BehaviorTreeComponent->IsValidLowLevelFast();
}

bool AMonster6Controller::IsValidBlackBoard() const
{
	return Blackboard != nullptr && Blackboard->IsValidLowLevelFast();
}

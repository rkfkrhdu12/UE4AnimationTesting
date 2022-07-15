// Fill out your copyright notice in the Description page of Project Settings.


#include "ME/Monster6/BTTasks/FindRandomLocation.h"
#include "CharacterBase.h"
#include "AIController.h"
#include "AI/Navigation/NavigationTypes.h"
#include "NavigationSystem.h"
#include "ME/Monster6/Monster6_BBKeys.h"
#include "BehaviorTree/BlackboardComponent.h"

UFindRandomLocation::UFindRandomLocation()
{
    NodeName = TEXT("Find Random Location");
}

EBTNodeResult::Type UFindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    auto const controller = Cast<AAIController>(OwnerComp.GetAIOwner());
    auto const character = Cast<ACharacterBase>(controller->GetPawn());

    FVector CurLocation = character->GetActorLocation();
    FNavLocation MoveLocation;

    UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
    if (NavSystem->GetRandomPointInNavigableRadius(CurLocation, SearchRadius, MoveLocation, nullptr))
    {
        controller->GetBlackboardComponent()->SetValueAsVector(Monster6_BBKeys::TargetLocation, MoveLocation.Location);
    }

    FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

    return EBTNodeResult::Succeeded;
}

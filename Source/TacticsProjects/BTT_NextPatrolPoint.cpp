// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_NextPatrolPoint.h"
#include "EnemyPatrollingComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Engine/TargetPoint.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AIController.h"
#include "GameFramework/Pawn.h"

UBTT_NextPatrolPoint::UBTT_NextPatrolPoint()
{
	NodeName = "Update Patrol Point";
}

EBTNodeResult::Type UBTT_NextPatrolPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UEnemyPatrollingComponent* patrollingComp = Cast<UEnemyPatrollingComponent>(OwnerComp.GetAIOwner()->GetPawn()->GetComponentByClass(UEnemyPatrollingComponent::StaticClass()));

	if (patrollingComp)
	{
		ATargetPoint* nextPatrolPoint = patrollingComp->GetNextPatrolPoint();
		if (nextPatrolPoint)
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsObject(BlackboardKey.SelectedKeyName, nextPatrolPoint);
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}

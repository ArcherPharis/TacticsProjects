// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_ClearblackboardValue.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTT_ClearblackboardValue::UBTT_ClearblackboardValue()
{
	NodeName = TEXT("Clear BlackBoard Value");
}

EBTNodeResult::Type UBTT_ClearblackboardValue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
	return EBTNodeResult::Succeeded;
}

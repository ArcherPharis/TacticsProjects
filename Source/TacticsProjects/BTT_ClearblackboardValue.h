// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_ClearblackboardValue.generated.h"

/**
 * 
 */
UCLASS()
class TACTICSPROJECTS_API UBTT_ClearblackboardValue : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTT_ClearblackboardValue();

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};

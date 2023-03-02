// Fill out your copyright notice in the Description page of Project Settings.


#include "LVAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

ALVAIController::ALVAIController()
{
	PerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>("PerceptionComp");
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>("SightConfig");
	if (SightConfig)
	{
		PerceptionComp->ConfigureSense(*SightConfig);
		PerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &ALVAIController::PerceptionUpdated);
	}
}

void ALVAIController::BeginPlay()
{
	Super::BeginPlay();
	if (BehaviorTree)
	{
		RunBehaviorTree(BehaviorTree);
	}
}

void ALVAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	IGenericTeamAgentInterface* pawnInterface = Cast<IGenericTeamAgentInterface>(InPawn);
	if (pawnInterface)
	{
		TeamID = pawnInterface->GetGenericTeamId();
	}
}

void ALVAIController::PerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{

	if (Stimulus.WasSuccessfullySensed())
	{
		
		GetBlackboardComponent()->SetValueAsObject(TargetBlackboardKeyName, Actor);
	}
	else
	{
		auto PerceptionInfo = PerceptionComp->GetActorInfo(*Actor);
		if (!PerceptionInfo->HasAnyCurrentStimulus())
		{
			UE_LOG(LogTemp, Warning, TEXT("I lost track of: %s"), *Actor->GetName());
			GetBlackboardComponent()->ClearValue(TargetBlackboardKeyName);
			GetBlackboardComponent()->SetValueAsVector(LastSeenKeyName, Actor->GetActorLocation());
		}
	}
}

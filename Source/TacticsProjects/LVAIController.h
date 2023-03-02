// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "GenericTeamAgentInterface.h"
#include "LVAIController.generated.h"

/**
 * 
 */
UCLASS()
class TACTICSPROJECTS_API ALVAIController : public AAIController
{
	GENERATED_BODY()

public:

	ALVAIController();
	/** Assigns Team Agent to given TeamID */
	FORCEINLINE virtual void SetGenericTeamId(const FGenericTeamId& ID) { TeamID = ID; }

	/** Retrieve team identifier in form of FGenericTeamId */
	FORCEINLINE virtual FGenericTeamId GetGenericTeamId() const { return TeamID; }
private:

	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;


	FGenericTeamId TeamID;

	UPROPERTY(VisibleDefaultsOnly, Category = "Perception")
		class UAIPerceptionComponent* PerceptionComp;
	UPROPERTY()
		class UAISenseConfig_Sight* SightConfig;

	UFUNCTION()
	void PerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName TargetBlackboardKeyName {"Target"};
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName LastSeenKeyName {"LastKnownPlayerLocation"};
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UBehaviorTree* BehaviorTree;
	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "Enemy.generated.h"

/**
 * 
 */
UCLASS()
class TACTICSPROJECTS_API AEnemy : public ABaseCharacter
{
	GENERATED_BODY()

public:
	AEnemy();
	UFUNCTION(BlueprintCallable, Category = "Enemy")
	UBoxComponent* GetAttackingHitBox() const { return hitBox; }

	UFUNCTION(BlueprintImplementableEvent, Category = "Enemy")
	void LaunchTarget(float force, ACharacter* characterToLaunch);

	virtual void Attack();

	virtual void BeginPlay() override;

private:
	virtual void OnDeath() override;

	

	UPROPERTY(EditAnywhere, Category = "Patrolling")
	class UEnemyPatrollingComponent* PatrollingPoint;

	UPROPERTY(EditAnywhere, Category = "Attacking")
	UAnimMontage* AttackMontage;


	//TODO make this all a gameplay ability in the future.
	UPROPERTY(EditAnywhere, Category = "Attacking")
	class UBoxComponent* hitBox;

	UPROPERTY(EditAnywhere, Category = "Attacking")
	float attackForce = 600.f;

	UPROPERTY(EditAnywhere, Category = "Attacking")
	TSubclassOf<class UGameplayEffect> attackEffect;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);
	
};

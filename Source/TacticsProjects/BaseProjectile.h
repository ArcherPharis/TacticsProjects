// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "GameplayEffectTypes.h"
#include "BaseProjectile.generated.h"

/**
 * 
 */
UCLASS()
class TACTICSPROJECTS_API ABaseProjectile : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()

public:
	ABaseProjectile();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void DestroyProjectile(FHitResult result);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	USceneComponent* rootComp;


	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	class UProjectileMovementComponent* projectileMovementComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	class USphereComponent* hitSphere;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	FGameplayTag DamageEventTag;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	float projectileRange = 8000.f;

	UFUNCTION()
	void TargetOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	TArray<AActor*> CurrentTargets;

	FTimerHandle destroyTimer;

	void DestroyAfterTime();
};

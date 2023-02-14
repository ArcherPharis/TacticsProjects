// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"

ABaseProjectile::ABaseProjectile()
{
	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Comp"));
	SetRootComponent(rootComp);
	projectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Comp"));
	hitSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Hit Sphere"));
	hitSphere->SetupAttachment(RootComponent);
	
	hitSphere->SetCollisionResponseToAllChannels(ECR_Overlap);
}

void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(destroyTimer, this, &ABaseProjectile::DestroyAfterTime, 1.f, false);
	hitSphere->OnComponentBeginOverlap.AddDynamic(this, &ABaseProjectile::TargetOverlapped);
	FHitResult traceResult;
	FVector ViewLoc;
	FRotator ViewRot;
	FCollisionQueryParams CollisionParameters;
	CollisionParameters.AddIgnoredActor(this);
	CollisionParameters.AddIgnoredActor(GetOwner());
	GetOwner()->GetActorEyesViewPoint(ViewLoc, ViewRot);
	if (GetWorld()->LineTraceSingleByChannel(traceResult, ViewLoc, ViewLoc + ViewRot.Vector() * projectileRange, ECC_Camera, CollisionParameters))
	{
		
		FGameplayEventData eventData;		
		FGameplayAbilityTargetDataHandle TargetData = UAbilitySystemBlueprintLibrary::AbilityTargetDataFromActor(traceResult.GetActor());
		eventData.TargetData = TargetData;
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwner(), DamageEventTag, eventData);
		DestroyProjectile(traceResult);
	}
}


void ABaseProjectile::TargetOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//hitbox method
	//TArray<AActor*> potentialTargets;
	//hitSphere->GetOverlappingActors(potentialTargets);
	//
	//FGameplayEventData eventData;
	//FGameplayAbilityTargetDataHandle TargetData = UAbilitySystemBlueprintLibrary::AbilityTargetDataFromActorArray(potentialTargets, true);
	//eventData.TargetData = TargetData;
	//UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwner(), DamageEventTag, eventData);
	//DestroyProjectile();
	GetWorldTimerManager().ClearTimer(destroyTimer);
	Destroy();
}

void ABaseProjectile::DestroyAfterTime()
{
	Destroy();
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnemyPatrollingComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "LVAbilitySystemComponent.h"

AEnemy::AEnemy()
{
	PatrollingPoint = CreateDefaultSubobject<UEnemyPatrollingComponent>(TEXT("PatrollingComp"));
	hitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Hit Box"));
	hitBox->SetupAttachment(GetMesh());
}

void AEnemy::Attack()
{
	GetMesh()->GetAnimInstance()->Montage_Play(AttackMontage);
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	hitBox->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnHit);
}

void AEnemy::OnDeath()
{
	GetCapsuleComponent()->SetSimulatePhysics(true);
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Overlap);
	GetMesh()->SetSimulatePhysics(true);
	GetCharacterMovement()->DisableMovement();
}

void AEnemy::OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	ULVAbilitySystemComponent* ASC = OtherActor->FindComponentByClass<ULVAbilitySystemComponent>();
	if (ASC)
	{
		FGameplayEffectSpecHandle specHan = ASC->MakeOutgoingSpec(attackEffect, -1, ASC->MakeEffectContext());
		LaunchTarget(attackForce, Cast<ACharacter>(OtherActor));
		ASC->ApplyGameplayEffectSpecToSelf(*specHan.Data.Get());
	}
}

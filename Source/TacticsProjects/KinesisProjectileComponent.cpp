// Fill out your copyright notice in the Description page of Project Settings.


#include "KinesisProjectileComponent.h"
#include "LVAbilitySystemComponent.h"
#include "GameplayEffect.h"
#include "CoreUObject.h" 
#include "GameplayEffectTypes.h"
#include "ExecCalc_KinesisProjectile.h"


// Sets default values for this component's properties
UKinesisProjectileComponent::UKinesisProjectileComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UKinesisProjectileComponent::BeginPlay()
{
	Super::BeginPlay();
	GetOwner()->OnActorHit.AddDynamic(this, &UKinesisProjectileComponent::ActorHit);
	GetOwner()->OnActorBeginOverlap.AddDynamic(this, &UKinesisProjectileComponent::Contact);
	// ...
	
}


// Called every frame
void UKinesisProjectileComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
}

void UKinesisProjectileComponent::Contact(AActor* OverlappedActor, AActor* OtherActor)
{
	
	UE_LOG(LogTemp, Warning, TEXT("Made contact with: %s"), *OtherActor->GetName());
}

void UKinesisProjectileComponent::ActorHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor != SelfActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("Contact made"));
		ULVAbilitySystemComponent* ASC = OtherActor->FindComponentByClass<ULVAbilitySystemComponent>();
		if (ASC)
		{
			float speed = GetOwner()->GetVelocity().Length();
			float mass = 1.f;
			UPrimitiveComponent* PrimComp = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
			if (PrimComp)
			{
				mass = PrimComp->GetMass();
			}
			float damage = (speed * mass) / 500;
			FGameplayEffectSpecHandle specHan = ASC->MakeOutgoingSpec(contactGameplayEffect, -1, ASC->MakeEffectContext());
			specHan.Data.Get()->SetSetByCallerMagnitude(contactTag, damage);
			ASC->ApplyGameplayEffectSpecToSelf(*specHan.Data.Get());
			UE_LOG(LogTemp, Warning, TEXT("%f"), mass);

		}


		//TODO: consider doing the lines below if the velocity of the object is below a certain threshold.
		GetOwner()->OnActorHit.RemoveAll(this);
		UnregisterComponent();
		DestroyComponent();
	}
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "LVAbilitySystemComponent.h"
#include "LVAttributeSet.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"


// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AbilitySystemComp = CreateDefaultSubobject<ULVAbilitySystemComponent>("AbilitySystemComp");
	AttributeSet = CreateDefaultSubobject<ULVAttributeSet>("AttributeSet");
	ProjectileSpawnLocation = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnLocation"));
	ProjectileSpawnLocation->SetupAttachment(RootComponent);
	physicsHandleComponent = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandleComp"));

	PerceptionStimuliComp = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>("PerceptionStimuliComp");
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	ApplyInitialEffect();
	GetAbilitySystemComponent()->GetGameplayAttributeValueChangeDelegate(GetAttributeSet()->GetOxygenAttribute()).AddUObject(this, &ABaseCharacter::OxygenUpdated);
	GetAbilitySystemComponent()->GetGameplayAttributeValueChangeDelegate(GetAttributeSet()->GetHealthAttribute()).AddUObject(this, &ABaseCharacter::OnHealthChange);
	for (auto& abilityKeyValuePair : InitialAbilities)
	{
		GiveAbility(abilityKeyValuePair.Value, static_cast<int>(abilityKeyValuePair.Key), true);
	}
	
}

void ABaseCharacter::OnDeath()
{
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (reportHP)
	{
		float currentHP = GetAttributeSet()->GetHealth();
		UE_LOG(LogTemp, Warning, TEXT("hp: %f"), currentHP);
	}
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComp;
}

void ABaseCharacter::ApplyInitialEffect()
{
	for (auto& effect : InitialEffects)
	{
		ApplyEffectToSelf(effect);
	}
}

void ABaseCharacter::ApplyEffectToSelf(const TSubclassOf<class UGameplayEffect>& effectToApply, int level)
{
	FGameplayEffectSpecHandle Spec = AbilitySystemComp->MakeOutgoingSpec(effectToApply, level, AbilitySystemComp->MakeEffectContext());
	AbilitySystemComp->ApplyGameplayEffectSpecToSelf(*Spec.Data);
}

void ABaseCharacter::OxygenUpdated(const FOnAttributeChangeData& AttributeData)
{
}

void ABaseCharacter::OnHealthChange(const FOnAttributeChangeData& AttributeData)
{
	if (AttributeData.NewValue <= 0)
	{
		OnDeath();
	}
}

FGameplayAbilitySpec* ABaseCharacter::GiveAbility(const TSubclassOf<class UGameplayAbility>& newAbility, int inputID, bool broadCast, int level)
{
	FGameplayAbilitySpecHandle specHandle = AbilitySystemComp->GiveAbility(FGameplayAbilitySpec(newAbility, level, inputID));
	FGameplayAbilitySpec* spec = AbilitySystemComp->FindAbilitySpecFromHandle(specHandle);
	return spec;
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "LVAbilitySystemComponent.h"
#include "LVAttributeSet.h"
#include "AbilitySystemBlueprintLibrary.h"


// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AbilitySystemComp = CreateDefaultSubobject<ULVAbilitySystemComponent>("AbilitySystemComp");
	AttributeSet = CreateDefaultSubobject<ULVAttributeSet>("AttributeSet");


}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	ApplyInitialEffect();
	
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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


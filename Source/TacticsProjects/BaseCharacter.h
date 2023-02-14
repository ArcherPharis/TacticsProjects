// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"
#include "LVAbilityTypes.h"
#include "GameplayAbilitySpec.h"
#include "BaseCharacter.generated.h"

UCLASS()
class TACTICSPROJECTS_API ABaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const;
	FORCEINLINE class ULVAttributeSet* GetAttributeSet() const { return AttributeSet; }

	void ApplyInitialEffect();

	UFUNCTION(BlueprintCallable, Category = "PlayerCharacter")
	USceneComponent* GetProjectileSpawnLocation() const { return ProjectileSpawnLocation; }

protected:

	UFUNCTION(BlueprintCallable, Category = "GameplayAbility")
	void ApplyEffectToSelf(const TSubclassOf<class UGameplayEffect>& effectToApply, int level = -1);

	virtual void OxygenUpdated(const FOnAttributeChangeData& AttributeData);

private:
	UPROPERTY()
	class ULVAbilitySystemComponent* AbilitySystemComp;

	UPROPERTY()
	class ULVAttributeSet* AttributeSet;

	UPROPERTY(EditDefaultsOnly, Category = "GameplayAbility")
	TArray <TSubclassOf<class UGameplayEffect>> InitialEffects;

	UPROPERTY(EditDefaultsOnly, Category = "GameplayAbility")
	TMap<ELVAbilityInputID, TSubclassOf<class UGameplayAbility>> InitialAbilities;

	FGameplayAbilitySpec* GiveAbility(const TSubclassOf<class UGameplayAbility>& newAbility, int inputID = -1, bool broadCast = true, int level = 0);

	UPROPERTY(EditDefaultsOnly, Category = "Base Character")
	USceneComponent* ProjectileSpawnLocation;

};

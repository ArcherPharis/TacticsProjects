// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"
#include "LVAbilityTypes.h"
#include "GameplayAbilitySpec.h"
#include "GenericTeamAgentInterface.h"
#include "BaseCharacter.generated.h"

UCLASS()
class TACTICSPROJECTS_API ABaseCharacter : public ACharacter, public IAbilitySystemInterface, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnDeath();

public:
	/** Assigns Team Agent to given TeamID */
	FORCEINLINE virtual void SetGenericTeamId(const FGenericTeamId& ID) { TeamID = ID; }

	/** Retrieve team identifier in form of FGenericTeamId */
	FORCEINLINE virtual FGenericTeamId GetGenericTeamId() const { return TeamID; }
private:
	UPROPERTY(EditAnywhere, Category = "AI")
	FGenericTeamId TeamID;

	UPROPERTY()
	class UAIPerceptionStimuliSourceComponent* PerceptionStimuliComp;



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
	UFUNCTION(BlueprintCallable, Category = "PlayerCharacter")
	USceneComponent* GetKinesisLocation() const { return KinesisHoldingLocation; }

	UFUNCTION(BlueprintPure, Category = "BaseCharacter")
	UAnimMontage* GetFlinchMontage() const { return flinchMontage; }

	FORCEINLINE class UPhysicsHandleComponent* GetPhysicsHandleComponent() const { return physicsHandleComponent; }

protected:

	UFUNCTION(BlueprintCallable, Category = "GameplayAbility")
	void ApplyEffectToSelf(const TSubclassOf<class UGameplayEffect>& effectToApply, int level = -1);

	virtual void OxygenUpdated(const FOnAttributeChangeData& AttributeData);

	UPROPERTY(EditDefaultsOnly, Category = "Physics")
	USceneComponent* KinesisHoldingLocation;

private:
	UPROPERTY()
	class ULVAbilitySystemComponent* AbilitySystemComp;

	void OnHealthChange(const FOnAttributeChangeData& AttributeData);

	UPROPERTY(EditDefaultsOnly, Category = "Physics")
	UPhysicsHandleComponent* physicsHandleComponent;
	UPROPERTY(EditAnywhere, Category = "Interaction")
	bool reportHP = false;


	UPROPERTY()
	class ULVAttributeSet* AttributeSet;

	UPROPERTY(EditDefaultsOnly, Category = "GameplayAbility")
	TArray <TSubclassOf<class UGameplayEffect>> InitialEffects;

	UPROPERTY(EditDefaultsOnly, Category = "GameplayAbility")
	TMap<ELVAbilityInputID, TSubclassOf<class UGameplayAbility>> InitialAbilities;

	FGameplayAbilitySpec* GiveAbility(const TSubclassOf<class UGameplayAbility>& newAbility, int inputID = -1, bool broadCast = true, int level = 0);

	UPROPERTY(EditDefaultsOnly, Category = "Base Character")
	USceneComponent* ProjectileSpawnLocation;

	UPROPERTY(EditDefaultsOnly, Category = "Base Character")
	UAnimMontage* flinchMontage;

};

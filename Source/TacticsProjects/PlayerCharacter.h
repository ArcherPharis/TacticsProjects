// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "PlayerCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOxygenChange, float, newOxygen);
/**
 * 
 */
UCLASS()
class TACTICSPROJECTS_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	UFUNCTION(BlueprintCallable, Category = "Player")
	void Interact();
	UFUNCTION(BlueprintCallable, Category = "Player")
	void UpdateOxygenReservesFlat();

	UFUNCTION(BlueprintPure, Category = "Player Inventory")
	FORCEINLINE class UInventoryComponent* GetInventoryComponent() const { return inventoryComp; }

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	bool HasReservedOxygen();

	void RefillOxygen();

	FOnOxygenChange onOxygenChange;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Base Character")
	class UCameraComponent* playerEyes;

	UPROPERTY(EditDefaultsOnly, Category = "Base Character")
	UAnimMontage* grabAnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Base Character")
	class USpringArmComponent* springArm;

	UPROPERTY(EditDefaultsOnly, Category = "Base Character")
	UAnimMontage* DeathMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Interaction")
	UInventoryComponent* inventoryComp;

	UPROPERTY(EditDefaultsOnly, Category = "Interaction")
	float GrabRange = 200.f;

	virtual void OnDeath() override;


	//todo, when we change the Fire Ability to a new one, this class needs to change too.
	UPROPERTY(EditDefaultsOnly, Category = "GameplayAbility")
	TSubclassOf<class UGameplayAbility> FireAbility;

	UPROPERTY(EditDefaultsOnly, Category = "GameplayAbility")
	FGameplayTag BasicFireCombo;
	UPROPERTY(EditDefaultsOnly, Category = "GameplayAbility")
	FGameplayTag launchTag;


	UPROPERTY(EditDefaultsOnly, Category = "Player Stats")
	TSubclassOf<class UGameplayEffect> OutOfOxygenHealthDrainEffect;
	UPROPERTY(EditDefaultsOnly, Category = "Player Stats")
	FGameplayTagContainer OutOfOxygenTags;

	void MoveForward(float value);
	void MoveRight(float value);
	void LookUp(float value);
	void Turn(float value);
	void Fire();
	

	virtual void OxygenUpdated(const FOnAttributeChangeData& AttributeData) override;
	bool reachedZero = false;

	
};

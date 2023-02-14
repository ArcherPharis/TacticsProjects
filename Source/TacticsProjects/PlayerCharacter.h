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

	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	bool HasReservedOxygen();

	void RefillOxygen();

	FOnOxygenChange onOxygenChange;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Base Character")
	class UCameraComponent* playerEyes;

	UPROPERTY(EditDefaultsOnly, Category = "Base Character")
	class USpringArmComponent* springArm;



	UPROPERTY(EditDefaultsOnly, Category = "GameplayAbility")
	TSubclassOf<class UGameplayAbility> FireAbility;

	UPROPERTY(EditDefaultsOnly, Category = "GameplayAbility")
	FGameplayTag BasicFireCombo;

	UPROPERTY(EditDefaultsOnly, Category = "Player Stats")
	float reservedOxygen = 100.f;


	void MoveForward(float value);
	void MoveRight(float value);
	void LookUp(float value);
	void Turn(float value);
	void Fire();
	
};

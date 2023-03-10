// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "LVAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


/**
 * 
 */
UCLASS()
class TACTICSPROJECTS_API ULVAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

	UPROPERTY()
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(ULVAttributeSet, Health);

	UPROPERTY()
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(ULVAttributeSet, MaxHealth);

	UPROPERTY()
	FGameplayAttributeData Oxygen;
	ATTRIBUTE_ACCESSORS(ULVAttributeSet, Oxygen);

	UPROPERTY()
	FGameplayAttributeData MaxOxygen;
	ATTRIBUTE_ACCESSORS(ULVAttributeSet, MaxOxygen);

	UPROPERTY()
	FGameplayAttributeData ReservedOxygen;
	ATTRIBUTE_ACCESSORS(ULVAttributeSet, ReservedOxygen);

	UPROPERTY()
	FGameplayAttributeData MaxReservedOxygen;
	ATTRIBUTE_ACCESSORS(ULVAttributeSet, MaxReservedOxygen);

	UPROPERTY()
	FGameplayAttributeData Capcity;
	ATTRIBUTE_ACCESSORS(ULVAttributeSet, Capcity);

	UPROPERTY()
	FGameplayAttributeData MaxCapacity;
	ATTRIBUTE_ACCESSORS(ULVAttributeSet, MaxCapacity);

	UPROPERTY()
	FGameplayAttributeData Nourishment;
	ATTRIBUTE_ACCESSORS(ULVAttributeSet, Nourishment);

	UPROPERTY()
	FGameplayAttributeData MaxNourishment;
	ATTRIBUTE_ACCESSORS(ULVAttributeSet, MaxNourishment);

	UPROPERTY()
	FGameplayAttributeData Attunement;
	ATTRIBUTE_ACCESSORS(ULVAttributeSet, Attunement);
	UPROPERTY()
	FGameplayAttributeData Defense;
	ATTRIBUTE_ACCESSORS(ULVAttributeSet, Defense);
	UPROPERTY()
	FGameplayAttributeData Resistance;
	ATTRIBUTE_ACCESSORS(ULVAttributeSet, Resistance);

	UPROPERTY()
	FGameplayAttributeData Speed;
	ATTRIBUTE_ACCESSORS(ULVAttributeSet, Speed);



	UPROPERTY()
	FGameplayAttributeData FireStones;
	ATTRIBUTE_ACCESSORS(ULVAttributeSet, FireStones);

	UPROPERTY()
	FGameplayAttributeData IceStones;
	ATTRIBUTE_ACCESSORS(ULVAttributeSet, IceStones);

	UPROPERTY()
	FGameplayAttributeData ThunderStones;
	ATTRIBUTE_ACCESSORS(ULVAttributeSet, ThunderStones);

	UPROPERTY()
	FGameplayAttributeData WindStones;
	ATTRIBUTE_ACCESSORS(ULVAttributeSet, WindStones);

	UPROPERTY()
	FGameplayAttributeData Experience;
	ATTRIBUTE_ACCESSORS(ULVAttributeSet, Experience);

	UPROPERTY()
	FGameplayAttributeData Level;
	ATTRIBUTE_ACCESSORS(ULVAttributeSet, Level);

	UPROPERTY()
	FGameplayAttributeData MaxLevel;
	ATTRIBUTE_ACCESSORS(ULVAttributeSet, MaxLevel);
	
};

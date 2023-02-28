// Fill out your copyright notice in the Description page of Project Settings.


#include "FireDamageExecution.h"
#include "LVAttributeSet.h"



struct DamageCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Health);

	DamageCapture()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(ULVAttributeSet, Health, Target, true);

	}

};

static DamageCapture& GetDamageCapture()
{
	static DamageCapture DamageCaptureVar;
	return DamageCaptureVar;
}


UFireDamageExecution::UFireDamageExecution()
{
	RelevantAttributesToCapture.Add(GetDamageCapture().HealthDef);
	ValidTransientAggregatorIdentifiers.AddTag(FGameplayTag::RequestGameplayTag("Base.calc.damage"));

}

void UFireDamageExecution::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecParams, FGameplayEffectCustomExecutionOutput& ExecOutputs) const
{

	float OutHealth = 0.0f;

	float HealthMagnitude = 0.0f;
	float baseDamage = 0.0f;

	ExecParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageCapture().HealthDef, FAggregatorEvaluateParameters(), HealthMagnitude);
	ExecParams.AttemptCalculateTransientAggregatorMagnitude(FGameplayTag::RequestGameplayTag("Base.calc.damage"), FAggregatorEvaluateParameters(), baseDamage);


	bool bHasIce = ExecParams.GetTargetAbilitySystemComponent()->GetOwnerActor()->ActorHasTag("Ice");

	if (bHasIce)
	{
		baseDamage *= 2;
		
	}

	OutHealth = HealthMagnitude - baseDamage;
	ExecOutputs.AddOutputModifier(FGameplayModifierEvaluatedData(GetDamageCapture().HealthProperty, EGameplayModOp::Override, OutHealth));
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "ExecCalc_KinesisProjectile.h"
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


UExecCalc_KinesisProjectile::UExecCalc_KinesisProjectile()
{
	RelevantAttributesToCapture.Add(GetDamageCapture().HealthDef);
}


void UExecCalc_KinesisProjectile::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecParams, FGameplayEffectCustomExecutionOutput& ExecOutputs) const
{
	

	float OutHealth = 0.0f;


	float HealthMagnitude = 0.0f;
	float ContactDamage = 0.0f;

	//ExecParams.AttemptCalculateTransientAggregatorMagnitude(FGameplayTag::RequestGameplayTag("Exec.Kinesis.Contact"), FAggregatorEvaluateParameters(), ProjectileDamage);
	const FGameplayEffectSpec& Spec = ExecParams.GetOwningSpec();
	ContactDamage = Spec.GetSetByCallerMagnitude(TEXT("Executes.Kinesis.Contact"));
	ExecParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageCapture().HealthDef, FAggregatorEvaluateParameters(), HealthMagnitude);

	OutHealth = HealthMagnitude - ContactDamage;
	ExecOutputs.AddOutputModifier(FGameplayModifierEvaluatedData(GetDamageCapture().HealthProperty, EGameplayModOp::Override, OutHealth));
}


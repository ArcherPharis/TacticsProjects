// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LVAbilityTypes.generated.h"

UENUM(BlueprintType)
enum class ELVAbilityInputID : uint8
{
	None,
	Confirm,
	Cancel,
	Fire,
	SlotOne,
	SlotTwo,
	SlotThree,
	SlotFour,
	UseOxygen,
	Kinesis
};

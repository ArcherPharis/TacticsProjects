// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "Enemy.generated.h"

/**
 * 
 */
UCLASS()
class TACTICSPROJECTS_API AEnemy : public ABaseCharacter
{
	GENERATED_BODY()

private:
	virtual void OnDeath() override;
	
};

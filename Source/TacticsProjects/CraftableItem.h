// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "CraftableItem.generated.h"

/**
 * 
 */
UCLASS()
class TACTICSPROJECTS_API ACraftableItem : public ABaseItem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "ItemRecipe")
	TMap<TSubclassOf<ABaseItem>, int> GetCraftingRecipe() const { return CraftingRecipe; }


private:


	
};

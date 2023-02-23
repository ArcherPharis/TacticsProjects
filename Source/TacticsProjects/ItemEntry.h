// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "ItemEntry.generated.h"

/**
 * 
 */
UCLASS()
class TACTICSPROJECTS_API UItemEntry : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

private:

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject);
	UPROPERTY(meta = (BindWidget))
	class UImage* itemIcon;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* itemAmountText;

public:
	void UpdateAmountText(int newAmount);

	
};

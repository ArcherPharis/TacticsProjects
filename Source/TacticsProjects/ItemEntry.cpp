// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemEntry.h"
#include "BaseItem.h"
#include "PlayerCharacter.h"
#include "InventoryComponent.h"
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"

void UItemEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
	ABaseItem* item = Cast<ABaseItem>(ListItemObject);
	itemIcon->SetBrushFromTexture(item->GetItemIcon());
	APlayerCharacter* character = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	int* num = character->GetInventoryComponent()->GetInventory().Find(item->GetClass());
	itemAmountText->SetText(FText::FromString(FString::FromInt(*num)));
	
	
}

void UItemEntry::UpdateAmountText(int newAmount)
{
	itemAmountText->SetText(FText::FromString(FString::FromInt(newAmount)));
}

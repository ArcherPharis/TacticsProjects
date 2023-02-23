// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInventoryComponent::AddToInventory(TSubclassOf<ABaseItem> item, int amount)
{
	if (!Inventory.Find(item))
	{
		Inventory.Add(item, amount);
		//onNewItem.Broadcast(item->GetDefaultObject(), GetOwner());
	}
	else
	{
		int* quantity = Inventory.Find(item) + amount;
		Inventory.Add(item, FMath::Clamp(*quantity, 0, 99));
	}

	
}

bool UInventoryComponent::QueryInventory(TSubclassOf<ABaseItem> item, int amount, int& QuanityOfItem)
{
	//checks if we have enough of the item we need for a crafting recipe or something.
	if (Inventory.Find(item) && *Inventory.Find(item) >= amount)
	{
		QuanityOfItem = *Inventory.Find(item);
		return true;
	}
	return false;
}

void UInventoryComponent::RemoveFromInventory(TSubclassOf<ABaseItem> item, int amount)
{
	int quanitity;

	if (QueryInventory(item, amount, quanitity))
	{
		int amountOfItemLeft = quanitity - amount;
		Inventory.Add(item, amountOfItemLeft);
	}
}


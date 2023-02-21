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

void UInventoryComponent::AddToInventory(TSubclassOf<class ABaseItem> item, int amount)
{
	int* quantity = Inventory.Find(item) + amount;
	Inventory.Add(item, FMath::Clamp( *quantity, 0, 99));
}

bool UInventoryComponent::QueryInventory(TSubclassOf<class ABaseItem> item, int amount, int& QuanityOfItem)
{
	//checks if we have enough of the item we need for a crafting recipe or something.
	int* quanitity = Inventory.Find(item);

	if (amount >= *quanitity && Inventory.Find(item))
	{
		QuanityOfItem = *quanitity;
		return true;
	}
	else
	{
		QuanityOfItem = *quanitity;
		return false;
	}
	return false;
}

void UInventoryComponent::RemoveFromInventory(TSubclassOf<class ABaseItem> item, int amount)
{
	int quanitity;

	if (QueryInventory(item, amount, quanitity))
	{
		int amountOfItemLeft = quanitity - amount;
		Inventory.Add(item, amountOfItemLeft);
	}
}


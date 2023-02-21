// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractInterface.h"
#include "BaseItem.generated.h"

UENUM()
enum ItemType
{
	//ingredients
	Organic UMETA(DisplayName = "Organic"),
	Inorganic UMETA(DisplayName = "Inorganic"),
	Gem UMETA(DisplayName = "Gem"),
	//items
	Food UMETA(DisplayName = "Food"),
	Restorative UMETA(DisplayName = "Restorative"),
	BattleItem UMETA(DisplayName = "BattleItem"),
	AbilityGiving UMETA(DisplayName = "AbilityGiving")
};


UCLASS()
class TACTICSPROJECTS_API ABaseItem : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Item")
	FORCEINLINE FText GetItemName() const { return ItemName; }

	UFUNCTION(BlueprintCallable, Category = "Item")
	FORCEINLINE FText GetItemDescription() const { return ItemDescription; }

	UFUNCTION(BlueprintCallable, Category = "Item")
	FORCEINLINE UTexture2D* GetItemIcon() const { return ItemIcon; }

	UFUNCTION(BlueprintImplementableEvent)
	void LookAt(APlayerCharacter* player);
	UFUNCTION(BlueprintImplementableEvent)
	void InteractWith(APlayerCharacter* player);

private:


	UPROPERTY(EditDefaultsOnly, Category = "Item", meta = (MultiLine = true))
	FText ItemName;

	UPROPERTY(EditDefaultsOnly, Category = "Item", meta = (MultiLine = true))
	FText ItemDescription;

	UPROPERTY(EditDefaultsOnly, Category = "Item", meta = (MultiLine = true))
	UTexture2D* ItemIcon;

	UPROPERTY(EditDefaultsOnly, Category = "Item", meta = (MultiLine = true))
	bool bIsCraftable = false;

	UPROPERTY(EditDefaultsOnly, Category = "Item")
	TEnumAsByte<ItemType> itemType;

	UPROPERTY(EditDefaultsOnly, Category = "Item")
	UStaticMeshComponent* ItemMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Item")
	USceneComponent* RootComp;



};

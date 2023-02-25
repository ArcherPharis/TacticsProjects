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
	BattleItem UMETA(DisplayName = "Battle Item"),
	AbilityGiving UMETA(DisplayName = "Special")
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

	UFUNCTION(BlueprintCallable, Category = "Default")
	FORCEINLINE FText GetItemName() const { return ItemName; }

	UFUNCTION(BlueprintCallable, Category = "Default")
	FORCEINLINE FText GetItemDescription() const { return ItemDescription; }

	UFUNCTION(BlueprintCallable, Category = "Default")
	FORCEINLINE UTexture2D* GetItemIcon() const { return ItemIcon; }

	UFUNCTION(BlueprintImplementableEvent)
	void LookAt(APlayerCharacter* player);
	UFUNCTION(BlueprintImplementableEvent)
	void InteractWith(APlayerCharacter* player);

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default", meta = (MultiLine = true))
		FText ItemName;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default", meta = (MultiLine = true))
		FText ItemDescription;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default")
		UTexture2D* ItemIcon;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default")
	bool bIsCraftable = false;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default")
	TSubclassOf<class UGameplayEffect> effectToApply;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default")
	TEnumAsByte<ItemType> itemType;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default")
	TMap<TSubclassOf<ABaseItem>, int> CraftingRecipe;


private:



	UPROPERTY(EditDefaultsOnly, Category = "Item")
	UStaticMeshComponent* ItemMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Item")
	USceneComponent* RootComp;





};

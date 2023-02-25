// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractInterface.h"
#include "BaseWorldOnlyItem.generated.h"

UCLASS()
class TACTICSPROJECTS_API ABaseWorldOnlyItem : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseWorldOnlyItem();

	UFUNCTION(BlueprintImplementableEvent)
	void LookAt(APlayerCharacter* player);
	UFUNCTION(BlueprintImplementableEvent)
	void InteractWith(APlayerCharacter* player);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

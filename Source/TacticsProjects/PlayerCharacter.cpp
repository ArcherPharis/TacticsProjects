// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "InventoryComponent.h"
#include "LVAbilityTypes.h"
#include "LVAttributeSet.h"

APlayerCharacter::APlayerCharacter()
{
	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("springArm"));
	springArm->SetupAttachment(GetMesh(), TEXT("headSocket"));
	playerEyes = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Eyes"));
	playerEyes->SetupAttachment(springArm);
	KinesisHoldingLocation = CreateDefaultSubobject<USceneComponent>(TEXT("KinesisLocation"));
	KinesisHoldingLocation->SetupAttachment(playerEyes);
	inventoryComp = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory Comp"));

}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	//GetMesh()->AttachToComponent(playerEyes, FAttachmentTransformRules::KeepWorldTransform);
	GetProjectileSpawnLocation()->AttachToComponent(playerEyes, FAttachmentTransformRules::KeepRelativeTransform);
	onOxygenChange.Broadcast(GetAttributeSet()->GetReservedOxygen());
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	GetPhysicsHandleComponent()->SetTargetLocation(GetKinesisLocation()->GetComponentLocation());
}


void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APlayerCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &APlayerCharacter::Turn);
	PlayerInputComponent->BindAction(TEXT("Jump"),IE_Pressed,  this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &APlayerCharacter::Fire);
	PlayerInputComponent->BindAction(TEXT("Interact"), IE_Pressed, this, &APlayerCharacter::Interact);
	GetAbilitySystemComponent()->BindAbilityActivationToInputComponent(PlayerInputComponent, FGameplayAbilityInputBinds("Confirm",
		"Cancel",
		"ELVAbilityInputID",
		static_cast<int32>(ELVAbilityInputID::Confirm),
		static_cast<int32>(ELVAbilityInputID::Cancel)));

}

bool APlayerCharacter::HasReservedOxygen()
{


	if (GetAttributeSet()->GetReservedOxygen() > 0 && GetAttributeSet()->GetOxygen() != GetAttributeSet()->GetMaxOxygen())
	{
		return true;
	}

	return false;
}

void APlayerCharacter::RefillOxygen()
{ 
	float currentOxygenPercent = (GetAttributeSet()->GetOxygen() / GetAttributeSet()->GetMaxOxygen()) * 100 ;
	if (GetAttributeSet()->GetReservedOxygen() >= 100)
	{
		//reserved oxygen is at 100 percent or greater
		if (currentOxygenPercent == 0)
		{
			GetAttributeSet()->SetReservedOxygen(GetAttributeSet()->GetReservedOxygen() - 100);
			GetAttributeSet()->SetOxygen(GetAttributeSet()->GetMaxOxygen());
			onOxygenChange.Broadcast(GetAttributeSet()->GetReservedOxygen());

		}
		else
		{
			float percentReq = 100 - currentOxygenPercent; //say we had 30 left, so we'd need 70.
			GetAttributeSet()->SetReservedOxygen(GetAttributeSet()->GetReservedOxygen() - percentReq); //this was 100, taking away 70 gives us 30 remaining.
			//we're giving oxygen 70%, so we'd need 70% of our max oxygen
			GetAttributeSet()->SetOxygen(GetAttributeSet()->GetOxygen() + (GetAttributeSet()->GetMaxOxygen() * (percentReq/100)));
			onOxygenChange.Broadcast(GetAttributeSet()->GetReservedOxygen());
		}

	}
	else
	{
		float percentReq = 100 - currentOxygenPercent;

		if (GetAttributeSet()->GetReservedOxygen() > percentReq)
		{
			GetAttributeSet()->SetReservedOxygen(GetAttributeSet()->GetReservedOxygen() - percentReq);
			GetAttributeSet()->SetOxygen(GetAttributeSet()->GetOxygen() + (GetAttributeSet()->GetMaxOxygen() * (percentReq / 100)));
			onOxygenChange.Broadcast(GetAttributeSet()->GetReservedOxygen());
		}
		else
		{
			GetAttributeSet()->SetOxygen(GetAttributeSet()->GetOxygen() + (GetAttributeSet()->GetMaxOxygen() * (GetAttributeSet()->GetReservedOxygen()/ 100)));
			GetAttributeSet()->SetReservedOxygen(0);
			onOxygenChange.Broadcast(GetAttributeSet()->GetReservedOxygen());
		}

	}
}

void APlayerCharacter::MoveForward(float value)
{
	
	AddMovementInput(GetActorForwardVector() * value);
}

void APlayerCharacter::MoveRight(float value)
{
	AddMovementInput(GetActorRightVector() * value);
}

void APlayerCharacter::LookUp(float value)
{
	AddControllerPitchInput(value);
}

void APlayerCharacter::Turn(float value)
{
	AddControllerYawInput(value);
}

void APlayerCharacter::Fire()
{
	//todo the eventual Rune class would have a method that would have something like:get firing ability
	FGameplayAbilitySpec* FireAbilitySpec = GetAbilitySystemComponent()->FindAbilitySpecFromClass(FireAbility);
	if (FireAbilitySpec->IsActive())
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, BasicFireCombo, FGameplayEventData());
	}
	else
	{
		GetAbilitySystemComponent()->TryActivateAbilityByClass(FireAbility);
	}
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, launchTag, FGameplayEventData());
}

void APlayerCharacter::Interact()
{
	FHitResult traceResult;
	FVector ViewLoc;
	FRotator ViewRot;
	FCollisionQueryParams CollisionParameters;
	//CollisionParameters.AddIgnoredActor(this);
	GetActorEyesViewPoint(ViewLoc, ViewRot);
	if (GetWorld()->LineTraceSingleByChannel(traceResult, ViewLoc, ViewLoc + ViewRot.Vector() * GrabRange, ECC_GameTraceChannel2, CollisionParameters))
	{
		if (traceResult.bBlockingHit)
		{
			
			AActor* hitActor = traceResult.GetActor();
			IInteractInterface* interactInferface = Cast<IInteractInterface>(hitActor);
			interactInferface->Execute_InteractWith(hitActor, this);
			
		}
	}
}


void APlayerCharacter::OxygenUpdated(const FOnAttributeChangeData& AttributeData)
{
	Super::OxygenUpdated(AttributeData);
	if (AttributeData.NewValue == 0 && !reachedZero)
	{
		reachedZero = true;
		FGameplayEffectContextHandle handle;
		GetAbilitySystemComponent()->ApplyGameplayEffectToSelf(OutOfOxygenHealthDrainEffect.GetDefaultObject(), -1, handle);
	}
	else if(AttributeData.NewValue > 0)
	{
		GetAbilitySystemComponent()->RemoveActiveEffectsWithTags(OutOfOxygenTags);
		reachedZero = false;
	}
}

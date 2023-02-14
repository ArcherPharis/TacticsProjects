// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "LVAbilityTypes.h"
#include "LVAttributeSet.h"

APlayerCharacter::APlayerCharacter()
{
	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("springArm"));
	springArm->SetupAttachment(GetMesh(), TEXT("headSocket"));
	playerEyes = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Eyes"));
	playerEyes->SetupAttachment(springArm);

}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	//GetMesh()->AttachToComponent(playerEyes, FAttachmentTransformRules::KeepWorldTransform);
	GetProjectileSpawnLocation()->AttachToComponent(playerEyes, FAttachmentTransformRules::KeepRelativeTransform);
	onOxygenChange.Broadcast(reservedOxygen);
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
	GetAbilitySystemComponent()->BindAbilityActivationToInputComponent(PlayerInputComponent, FGameplayAbilityInputBinds("Confirm",
		"Cancel",
		"ELVAbilityInputID",
		static_cast<int32>(ELVAbilityInputID::Confirm),
		static_cast<int32>(ELVAbilityInputID::Cancel)));

}

bool APlayerCharacter::HasReservedOxygen()
{


	if (reservedOxygen > 0 && GetAttributeSet()->GetOxygen() != GetAttributeSet()->GetMaxOxygen())
	{
		return true;
	}

	return false;
}

void APlayerCharacter::RefillOxygen()
{ 
	float currentOxygenPercent = (GetAttributeSet()->GetOxygen() / GetAttributeSet()->GetMaxOxygen()) * 100 ;
	if (reservedOxygen >= 100)
	{
		//reserved oxygen is at 100 percent or greater
		if (currentOxygenPercent == 0)
		{
			reservedOxygen -= 100;
			GetAttributeSet()->SetOxygen(GetAttributeSet()->GetMaxOxygen());
			onOxygenChange.Broadcast(reservedOxygen);

		}
		else
		{
			float percentReq = 100 - currentOxygenPercent; //say we had 30 left, so we'd need 70.
			reservedOxygen -= percentReq; //this was 100, taking away 70 gives us 30 remaining.
			//we're giving oxygen 70%, so we'd need 70% of our max oxygen
			GetAttributeSet()->SetOxygen(GetAttributeSet()->GetOxygen() + (GetAttributeSet()->GetMaxOxygen() * (percentReq/100)));
			onOxygenChange.Broadcast(reservedOxygen);
		}

	}
	else
	{
		float percentReq = 100 - currentOxygenPercent;

		if (reservedOxygen > percentReq)
		{
			reservedOxygen -= percentReq;
			GetAttributeSet()->SetOxygen(GetAttributeSet()->GetOxygen() + (GetAttributeSet()->GetMaxOxygen() * (percentReq / 100)));
			onOxygenChange.Broadcast(reservedOxygen);
		}
		else
		{
			GetAttributeSet()->SetOxygen(GetAttributeSet()->GetOxygen() + (GetAttributeSet()->GetMaxOxygen() * (reservedOxygen / 100)));
			reservedOxygen = 0;
			onOxygenChange.Broadcast(reservedOxygen);
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
	UE_LOG(LogTemp, Warning, TEXT("Sending Event"));
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
}

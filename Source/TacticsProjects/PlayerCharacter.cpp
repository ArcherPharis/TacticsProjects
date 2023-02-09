// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

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
}


void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APlayerCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &APlayerCharacter::Turn);
	PlayerInputComponent->BindAction(TEXT("Jump"),IE_Pressed,  this, &ACharacter::Jump);

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

// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_Kinesis.h"
#include "LVAbilitySystemBlueprintLibrary.h"
#include "BaseCharacter.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitInputRelease.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "KinesisProjectileComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

void UGA_Kinesis::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	UAbilityTask_PlayMontageAndWait* MontagePlay = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, kinesisMontage);
	if (MontagePlay)
	{
		MontagePlay->OnBlendOut.AddDynamic(this, &UGA_Kinesis::MontageOut);
		MontagePlay->OnCancelled.AddDynamic(this, &UGA_Kinesis::MontageOut);
		//MontagePlay->OnInterrupted.AddDynamic(this, &UGA_Kinesis::MontageOut);
		MontagePlay->ReadyForActivation();
	}

	UAbilityTask_WaitInputRelease* releaseInput = UAbilityTask_WaitInputRelease::WaitInputRelease(this, false);

	releaseInput->OnRelease.AddDynamic(this, &UGA_Kinesis::PlayerReleasedInput);
	
	UAbilityTask_WaitGameplayEvent* WaitTargetStart = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, BeginKinesisTag);
	if (WaitTargetStart)
	{
		WaitTargetStart->EventReceived.AddDynamic(this, &UGA_Kinesis::BeginKinesis);
		WaitTargetStart->ReadyForActivation();
	}

	UAbilityTask_WaitGameplayEvent* WaitLaunchEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, fireObjectTag);
	if (WaitLaunchEvent)
	{
		WaitLaunchEvent->EventReceived.AddDynamic(this, &UGA_Kinesis::LaunchTarget);
		WaitLaunchEvent->ReadyForActivation();
	}

	UAbilityTask_WaitGameplayEvent* WaitNoTarget = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, autoEndKinesisTag);
	if (WaitNoTarget)
	{
		WaitNoTarget->EventReceived.AddDynamic(this, &UGA_Kinesis::EndKinesisNoTarget);
		WaitNoTarget->ReadyForActivation();
	}
	
}

void UGA_Kinesis::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UGA_Kinesis::PlayerReleasedInput(float timeHeld)
{
	ReleaseHeldItem();
}

void UGA_Kinesis::MontageOut()
{
	ReleaseHeldItem();
}

void UGA_Kinesis::BeginKinesis(FGameplayEventData Payload)
{
	if (!kinesisActivated)
	{
		kinesisActivated = true;

		FHitResult traceResult;
		FVector ViewLoc;
		FRotator ViewRot;
		FCollisionQueryParams CollisionParameters;
		CollisionParameters.AddIgnoredActor(GetOwningActorFromActorInfo());
		GetBaseCharacterAvatar()->GetActorEyesViewPoint(ViewLoc, ViewRot);
		FCollisionShape shape = FCollisionShape::MakeBox(FVector3d(80, 80, 80));
		//GetWorld()->LineTraceSingleByChannel(traceResult, ViewLoc, ViewLoc + ViewRot.Vector() * kinesisRange, ECC_Visibility, CollisionParameters)
		if (GetWorld()->SweepSingleByChannel(traceResult, ViewLoc, ViewLoc + ViewRot.Vector() * kinesisRange, FQuat::Identity, ECC_GameTraceChannel1, shape, CollisionParameters))
		{
			if (traceResult.GetComponent()->IsSimulatingPhysics())
			{
				traceResult.GetComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
				traceResult.GetComponent()->WakeRigidBody();
				GetBaseCharacterAvatar()->GetPhysicsHandleComponent()->GrabComponentAtLocation(traceResult.Component.Get(), NAME_None, traceResult.GetComponent()->GetComponentLocation());

			}


		}
	}
}

void UGA_Kinesis::LaunchTarget(FGameplayEventData Payload)
{
	if (GetBaseCharacterAvatar()->GetPhysicsHandleComponent()->GetGrabbedComponent())
	{
		K2_CommitAbility();
		UPrimitiveComponent* comp = GetBaseCharacterAvatar()->GetPhysicsHandleComponent()->GetGrabbedComponent();
		AActor* launchedActor = comp->GetOwner();
		if (launchedActor)
		{
			UE_LOG(LogTemp, Warning, TEXT("added comp"));
			 launchedActor->AddComponentByClass(kinesisComponent, false, launchedActor->GetTransform(), false);
			 comp->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
		}
		GetBaseCharacterAvatar()->GetPhysicsHandleComponent()->ReleaseComponent();
		FVector ViewLoc;
		FRotator ViewRot;
		GetBaseCharacterAvatar()->GetActorEyesViewPoint(ViewLoc, ViewRot);
		comp->AddImpulse( ViewRot.Vector() * launchForce, NAME_None, true);
		UAbilityTask_PlayMontageAndWait* MontagePlay = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, launchTargetMontage);
		if (MontagePlay)
		{
			MontagePlay->OnBlendOut.AddDynamic(this, &UGA_Kinesis::MontageOut);
			MontagePlay->OnCancelled.AddDynamic(this, &UGA_Kinesis::MontageOut);
			MontagePlay->OnInterrupted.AddDynamic(this, &UGA_Kinesis::MontageOut);
			MontagePlay->OnCompleted.AddDynamic(this, &UGA_Kinesis::MontageOut);
			MontagePlay->ReadyForActivation();
		}
		
	}
}

void UGA_Kinesis::EndKinesisNoTarget(FGameplayEventData Payload)
{
	if (!GetBaseCharacterAvatar()->GetPhysicsHandleComponent()->GetGrabbedComponent())
	{
		K2_EndAbility();
	}
}

void UGA_Kinesis::ReleaseHeldItem()
{
	if (GetBaseCharacterAvatar()->GetPhysicsHandleComponent()->GetGrabbedComponent())
	{
		GetBaseCharacterAvatar()->GetPhysicsHandleComponent()->GetGrabbedComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
		GetBaseCharacterAvatar()->GetPhysicsHandleComponent()->ReleaseComponent();
		

	}
	K2_EndAbility();

}


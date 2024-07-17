// Copyright 2024 All Rights Reserved by J&K


#include "JK1PCAnimInstance.h"
#include "JK1PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(JK1PCAnimInstance)

void UJK1PCAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Character = Cast<ACharacter>(TryGetPawnOwner());
	if (Character)
		MovementComponent = Character->GetCharacterMovement();
}

void UJK1PCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (MovementComponent == nullptr)
		return;

	// Set Speed & IsinAir
	Speed = Character->GetVelocity().Length();
	IsInAir = MovementComponent->IsFalling();

	// Set Roll & Pitch & Yaw
	{
		const FRotator AimRotator = Character->GetBaseAimRotation();
		const FRotator ActorRotator = Character->GetActorRotation();
		const FRotator DiffRotator = UKismetMathLibrary::NormalizedDeltaRotator(AimRotator, ActorRotator);

		Pitch = DiffRotator.Pitch;
		Roll = DiffRotator.Roll;
		Yaw = DiffRotator.Yaw;
	}

	// Setting Yaw Delta for Leans
	{
		const FRotator CurrentRotation = Character->GetActorRotation();
		const FRotator DiffRotation = UKismetMathLibrary::NormalizedDeltaRotator(RotationLastTick, CurrentRotation);
		float Target = DiffRotation.Yaw / DeltaSeconds / 7.f;
		YawDelta = UKismetMathLibrary::FInterpTo(YawDelta, Target, DeltaSeconds, 6.f);
		RotationLastTick = CurrentRotation;
	}

	// Set is Acceleraing
	IsAccelerating = MovementComponent->GetCurrentAcceleration().Length() > 0;

	// Set IsFullBody
	FullBody = GetCurveValue("FUllBody") > 0;
}

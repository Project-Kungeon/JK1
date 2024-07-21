// Copyright 2024 All Rights Reserved by J&K


#include "JK1Assassin.h"
#include "../../JK1CreatureStatComponent.h"
#include "JK1/Physics/JK1Collision.h"
#include "Animation/AnimMontage.h"
#include "Kismet/KismetSystemLibrary.h"


AJK1Assassin::AJK1Assassin()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> DefaultMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonKallari/Characters/Heroes/Kallari/Skins/Rogue/Meshes/Kallari_Rogue.Kallari_Rogue'"));
	if (DefaultMesh.Succeeded())
		Super::GetMesh()->SetSkeletalMesh(DefaultMesh.Object);

	CreatureStat->SetOwner(true, FName("Assassin"));
}

void AJK1Assassin::BeginPlay()
{
	Super::BeginPlay();
}

void AJK1Assassin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bWeaponActive)
		CheckWeaponTrace();
}

void AJK1Assassin::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AJK1Assassin::Attack()
{
	Super::Attack();
}

void AJK1Assassin::ComboActionBegin()
{
	Super::ComboActionBegin();
	
}

void AJK1Assassin::DoCombo()
{
	Super::DoCombo();
	switch (CurrentCombo)
	{
	case 0:
		CurrentCombo = 1;
		PlayAnimMontage(ComboActionMontage1, 1.f);
		break;
	case 1:
		CurrentCombo = 2;
		PlayAnimMontage(ComboActionMontage2, 1.f);
		break;
	case 2:
		CurrentCombo = 3;
		PlayAnimMontage(ComboActionMontage3, 1.f);
		break;
	}
	
}

void AJK1Assassin::ComboActionEnd()
{
	Super::ComboActionEnd();
}

void AJK1Assassin::SkillQ(const FInputActionValue& value)
{
	Super::SkillQ(value);
	UE_LOG(LogAssassin, Log, TEXT("This is %s"), *this->GetName());
}

void AJK1Assassin::CheckWeaponTrace()
{
	if (!bWeaponActive)
		return;

	FVector StartL = GetMesh()->GetSocketLocation(FName(TEXT("sword_base_l")));
	FVector StartR = GetMesh()->GetSocketLocation(FName(TEXT("sword_base_l")));
	FVector EndL = GetMesh()->GetSocketLocation(FName(TEXT("sword_tip_r")));
	FVector EndR = GetMesh()->GetSocketLocation(FName(TEXT("sword_tip_r")));
	FVector ExtendL = EndL - StartL;
	FVector ExtendR = EndR - StartR;
	const float AttackRadius = 20.f;

	TArray<FHitResult> HitResults;
	FCollisionQueryParams Params(SCENE_QUERY_STAT(Attack), false, this);


	bool bSuccessL = GetWorld()->SweepMultiByChannel(
		HitResults,
		StartL,
		EndL,
		FQuat::Identity,
		CCHANNEL_JK1ACTION,
		FCollisionShape::MakeCapsule(ExtendL),
		Params
	);

	bool bSuccessR = GetWorld()->SweepMultiByChannel(
		HitResults,
		StartR,
		EndR,
		FQuat::Identity,
		CCHANNEL_JK1ACTION,
		FCollisionShape::MakeCapsule(ExtendR),
		Params
	);

	if (bSuccessL || bSuccessR)
	{
		// FDamageEvent DamageEvent;

		for (FHitResult& HitResult : HitResults)
		{
			AActor* Actor = HitResult.GetActor();
			if (Actor == nullptr)
				continue;

			if (WeaponAttackTargets.Contains(Actor) == false)
			{
				WeaponAttackTargets.Add(Actor);

				// TODO HitDamage
				UE_LOG(LogTemp, Log, TEXT("HitDamage: %s"), *Actor->GetName());

			}
		}
	}
#if ENABLE_DRAW_DEBUG
	FVector DirectionL = EndL - StartL;
	FVector DirectionR = EndR - StartR;
	float CapsuleHalfHeightL = DirectionL.Size() / 2.f;
	float CapsuleHalfHeightR = DirectionR.Size() / 2.f;
	FVector CapsuleOriginL = StartL + (EndL - StartL) / 2.f;
	FVector CapsuleOriginR = StartR + (EndR - StartR) / 2.f;
	FColor DrawColor = bSuccessL || bSuccessR ? FColor::Green : FColor::Red;
	FQuat QuatRotationL = FQuat::FindBetweenNormals(FVector::UpVector, DirectionL.GetSafeNormal());
	FQuat QuatRotationR = FQuat::FindBetweenNormals(FVector::UpVector, DirectionR.GetSafeNormal());

	DrawDebugCapsule(
		GetWorld(),
		CapsuleOriginL,
		CapsuleHalfHeightL,
		AttackRadius,
		QuatRotationL,
		DrawColor,
		false,
		1.f,
		0
	);

	DrawDebugCapsule(
		GetWorld(),
		CapsuleOriginR,
		CapsuleHalfHeightR,
		AttackRadius,
		QuatRotationR,
		DrawColor,
		false,
		1.f,
		0
	);

#endif
}
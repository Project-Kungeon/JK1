// Copyright 2024 All Rights Reserved by J&K


#include "Creature/Monster/Boss/JK1Rampage.h"
#include "Creature/JK1CreatureStatComponent.h"
#include "Creature/PC/JK1PlayerCharacter.h"
#include "Controller/Monster/JK1RampageController.h"
#include "Components/CapsuleComponent.h"
#include "Physics/JK1Collision.h"
#include "Engine/DamageEvents.h"

AJK1Rampage::AJK1Rampage()
{
	// Default Settings
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> DefaultMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonRampage/Characters/Heroes/Rampage/Skins/Tier2/Elemental/Meshes/Rampage_Elemental.Rampage_Elemental'"));
	if (DefaultMesh.Succeeded())
		Super::GetMesh()->SetSkeletalMesh(DefaultMesh.Object);

	Super::GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -75.f), FRotator(0, -90.f, 0));
	Super::GetCapsuleComponent()->SetCapsuleHalfHeight(75.f);

	// AI
	// AIControllerClass = AJK1RampageController::StaticClass();
	// AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	CreatureStat->SetOwner(false, FName("Rampage"));
	CurrentCombo = 0;
	FistType = true;
}

void AJK1Rampage::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LogMonster, Log, TEXT("Rampage : Beginplay Call"));

	GetWorldTimerManager().ClearTimer(AnimHandle);
	//CreatureStat->OnHPIsZero.AddDynamic(this, &AJK1Rampage::Death);
}

void AJK1Rampage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AJK1Rampage::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AJK1Rampage::BasicAttack()
{
	UE_LOG(LogMonster, Log, TEXT("Attack"));

	switch (CurrentCombo)
	{
	case 0:
		PlayAnimMontage(ComboActionMontage1, 1.f);	
		break;
	case 1:
		PlayAnimMontage(ComboActionMontage2, 1.f);
		break;
	case 2:
		PlayAnimMontage(ComboActionMontage3, 1.f);
		CurrentCombo = 0;
		break;
	}

	OnAttackEnd.Broadcast();
}

void AJK1Rampage::Roar()
{
	UE_LOG(LogMonster, Log, TEXT("Roar!!!!!!!!!"));
	
	PlayAnimMontage(RoarMontage, 0.3f);
	
	//OnGimmicEnd.Broadcast();
}

void AJK1Rampage::EarthQuake()
{
	UE_LOG(LogMonster, Log, TEXT("Earthquake"));
	OnGimmicEnd.Broadcast();
}

void AJK1Rampage::GroundSmash()
{
	UE_LOG(LogMonster, Log, TEXT("GroundSmash"));
}

void AJK1Rampage::ThrowAway()
{
	UE_LOG(LogMonster, Log, TEXT("ThrowAway"));
}

void AJK1Rampage::EnhancedAttack()
{
	UE_LOG(LogMonster, Log, TEXT("EnhancedAttack"));

	PlayAnimMontage(EnhancedAttackMontage, 0.5f);

	OnGimmicEnd.Broadcast();
}

void AJK1Rampage::CheckBATrace()
{
	Super::CheckBATrace();

	if (!bBAActive)
		return; 

	bool IsRight = (CurrentCombo % 2 == 0 ) ? true : false;

	FVector StartL = GetMesh()->GetSocketLocation(FName(TEXT("lowerarm_lSocket")));
	FVector EndL = GetMesh()->GetSocketLocation(FName(TEXT("FX_Trail_L_01")));
	
	FVector StartR = GetMesh()->GetSocketLocation(FName(TEXT("lowerarm_rSocket")));
	FVector EndR = GetMesh()->GetSocketLocation(FName(TEXT("FX_Trail_R_01")));
	
	FVector ExtendL = EndL - StartL;
	FVector ExtendR = EndR - StartR;
	const float AttackRadius = 20.f;

	TArray<FHitResult> HitResults;
	FCollisionQueryParams Params(SCENE_QUERY_STAT(Attack), false, this);

	/*  sweep / multi / ByChannel */
	bool bSuccess = GetWorld()->SweepMultiByChannel(
		HitResults,
		IsRight ? StartR : StartL,
		IsRight ? EndR : EndL,
		FQuat::Identity,
		CCHANNEL_JK1ACTION,
		FCollisionShape::MakeCapsule(IsRight ? ExtendR : ExtendL),
		Params
	);
	

	if (bSuccess)
		ApplyDamageToTarget(HitResults, 1.f);
		

#if ENABLE_DRAW_DEBUG
	FVector DirectionL = EndL - StartL;
	FVector DirectionR = EndR - StartR;
	float CapsuleHalfHeightL = DirectionL.Size() / 2.f;
	float CapsuleHalfHeightR = DirectionR.Size() / 2.f;
	FVector CapsuleOriginL = StartL + (EndL - StartL) / 2.f;
	FVector CapsuleOriginR = StartR + (EndR - StartR) / 2.f;
	FColor DrawColor = bSuccess ? FColor::Green : FColor::Red;
	FQuat QuatRotationL = FQuat::FindBetweenNormals(FVector::UpVector, DirectionL.GetSafeNormal());
	FQuat QuatRotationR = FQuat::FindBetweenNormals(FVector::UpVector, DirectionR.GetSafeNormal());


	DrawDebugCapsule(
		GetWorld(),
		IsRight ? CapsuleOriginR : CapsuleOriginL,
		IsRight ? CapsuleHalfHeightR : CapsuleHalfHeightL,
		AttackRadius,
		IsRight ? QuatRotationR : QuatRotationL,
		DrawColor,
		false,
		1.f,
		0
	);
	
#endif
}

void AJK1Rampage::CheckFistTrace()
{
	FVector StartL = GetMesh()->GetSocketLocation(FName(TEXT("SmashLocationLeft")));
	FVector StartR = GetMesh()->GetSocketLocation(FName(TEXT("SmashLocationRight")));
	StartL.Z -= 100.f;
	StartR.Z -= 100.f;

	const float AttackRadius = 120.f;

	TArray<FHitResult> HitResults;
	FCollisionQueryParams Params(SCENE_QUERY_STAT(Attack), false, this);

	/*  sweep / multi / ByChannel */
	bool bSuccess = GetWorld()->SweepMultiByChannel(
		HitResults,
		FistType ? StartR : StartL,
		FistType ? StartR : StartL,
		FQuat::Identity,
		CCHANNEL_JK1ACTION,
		FCollisionShape::MakeSphere(AttackRadius),
		Params
	);


	if (bSuccess)
		ApplyDamageToTarget(HitResults, 30.f);

#if ENABLE_DRAW_DEBUG
	FColor DrawColor = bSuccess ? FColor::Green : FColor::Red;

	DrawDebugSphere(
		GetWorld(),
		FistType ? StartR : StartL,
		AttackRadius,
		26,
		DrawColor,
		false,
		1.f
	);
#endif
}

void AJK1Rampage::Death()
{
	Super::Death();

	UE_LOG(LogMonster, Log, TEXT("Rampage is down!!"));
}

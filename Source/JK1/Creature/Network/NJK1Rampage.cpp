// Copyright 2024 All Rights Reserved by J&K


#include "Creature/Network/NJK1Rampage.h"
#include "NJK1Rampage.h"
#include "Creature/JK1CreatureStatComponent.h"
#include "../../Creature/JK1CreatureBase.h"
#include "../../Creature/PC/JK1PlayerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Physics/JK1Collision.h"
#include "Engine/DamageEvents.h"

ANJK1Rampage::ANJK1Rampage()
	: AJK1Rampage()
{
}

void ANJK1Rampage::CheckBATrace()
{
	Super::CheckBATrace();
}

void ANJK1Rampage::CheckFistTrace()
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
	{
		message::C_Attack pkt;
		uint32 my_id = this->CreatureStat->GetCreatureInfo()->object_info().object_id();
		pkt.set_object_id(my_id);
		pkt.set_damage(30);
		for (FHitResult& HitResult : HitResults)
		{
			AActor* Actor = HitResult.GetActor();
			if (Actor == nullptr)
				continue;

			if (BasicAttackTargets.Contains(Actor) == false)
			{
				BasicAttackTargets.Add(Actor);

				if (AJK1PlayerCharacter* HitPawn = Cast<AJK1PlayerCharacter>(Actor))
				{
					if (HitPawn->isMyPlayer)
					{
						uint32 target_id = HitPawn->CreatureStat->GetCreatureInfo()->object_info().object_id();
						pkt.add_target_ids(target_id);
					}
					
				}
			}
		}
		SEND_PACKET(message::HEADER::PLAYER_ATTACK_REQ, pkt);
	}
		

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

void ANJK1Rampage::OnBasicAttackHit(TArray<FHitResult> HitResults)
{
	
	for (auto& HitResult : HitResults)
	{
		if (auto player = Cast<AJK1PlayerCharacter>(HitResult.GetActor()))
		{
			// 만약 내가 맞았다면
			if (player->isMyPlayer)
			{
				message::C_Attack pkt;
				uint32 my_id = this->CreatureStat->GetCreatureInfo()->object_info().object_id();
				pkt.set_object_id(my_id);
				pkt.set_damage(5);
				uint32 target_id = player->CreatureStat->GetCreatureInfo()->object_info().object_id();
				pkt.add_target_ids(target_id);
				SEND_PACKET(message::HEADER::PLAYER_ATTACK_REQ, pkt);
			}
		}
	}
	
}

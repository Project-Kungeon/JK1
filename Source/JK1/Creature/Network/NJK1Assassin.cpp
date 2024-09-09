// Copyright 2024 All Rights Reserved by J&K


#include "Creature/Network/NJK1Assassin.h"
#include "Creature/JK1CreatureStatComponent.h"
#include "JK1/Physics/JK1Collision.h"

ANJK1Assassin::ANJK1Assassin()
	: Super()
{
}

ANJK1Assassin::~ANJK1Assassin()
{
	delete PlayerInfo;
	delete DestInfo;
	PlayerInfo = nullptr;
	DestInfo = nullptr;
}

void ANJK1Assassin::BeginPlay()
{
	Super::BeginPlay();
}

void ANJK1Assassin::Tick(float DeltaTime)
{
	AJK1PlayerCharacter::Tick(DeltaTime);
	TArray<FHitResult> attackHits;
	if (bWeaponActive)
		attackHits = CheckWeaponTrace();
	if (MyTimeline)
		MyTimeline->TickComponent(DeltaTime, ELevelTick::LEVELTICK_TimeOnly, nullptr);

	if (!attackHits.IsEmpty())
	{
		message::C_Attack pkt;
		uint32 my_id = this->CreatureStat->GetCreatureInfo()->object_info().object_id();
		pkt.set_object_id(my_id);

		for (FHitResult& hit : attackHits)
		{
			
			AActor* actor = hit.GetActor();
			if (auto* Actor = Cast<AJK1CreatureBase>(actor))
			{
				uint32 target_id = Actor->CreatureStat->GetCreatureInfo()->object_info().object_id();
				
		//			SEND_PACKET(message::HEADER::ASSASSIN_E_REQ, ePkt);
		//			continue;
		//		}
		//		else
		//		{
		//			pkt.set_damage(13.f);
		//		}

				if (IsBackAttack(actor, hit))
				{
					// 백어택 데미지
					message::C_Attack backAttackPkt;
					backAttackPkt.set_object_id(my_id);
					backAttackPkt.set_damage(21.f);
					backAttackPkt.add_target_ids(target_id);
					//SEND_PACKET(message::HEADER::PLAYER_ATTACK_REQ, backAttackPkt);
				}
				if (IsBackAttack(actor, hit))
				{
					// 백어택 이펙트
					FVector HitLocation = hit.ImpactPoint;
					skill::C_Assassin_E ePkt;
					ePkt.set_object_id(my_id);
					ePkt.set_x(HitLocation.X);
					ePkt.set_y(HitLocation.Y);
					ePkt.set_z(HitLocation.Z);

					SEND_PACKET(message::HEADER::ASSASSIN_E_REQ, ePkt);
					continue;
				}
				else
				{
					pkt.set_damage(13.f);
				}

				pkt.add_target_ids(target_id);
			}
		}
		SEND_PACKET(message::HEADER::PLAYER_ATTACK_REQ, pkt);
	}

}

void ANJK1Assassin::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ANJK1Assassin::Move(const FInputActionValue& Value)
{
	Super::Move(Value);
}

void ANJK1Assassin::Look(const FInputActionValue& Value)
{
	Super::Look(Value);
}

void ANJK1Assassin::Attack()
{
	Super::Attack();
	if (isMyPlayer)
	{
		skill::C_ASSASSIN_Attack attackPkt;
		attackPkt.set_object_id(this->CreatureStat->GetCreatureInfo()->object_info().object_id());

		SEND_PACKET(message::HEADER::ASSASSIN_ATTACK_REQ, attackPkt);
	}
}

void ANJK1Assassin::SkillQ(const FInputActionValue& value)
{
	// Super::SkillQ(value);

	if (isMyPlayer)
	{
		skill::C_ASSASSIN_Q skillPkt;
		
		FVector SpawnPoint = GetActorLocation() + SpawnLocation;
		FRotator SpawnRotation = GetActorRotation();

		skillPkt.set_x(SpawnPoint.X);
		skillPkt.set_y(SpawnPoint.Y);
		skillPkt.set_z(SpawnPoint.Z);
		skillPkt.set_pitch(SpawnRotation.Pitch);
		skillPkt.set_yaw(SpawnRotation.Yaw);
		skillPkt.set_roll(SpawnRotation.Roll);
		skillPkt.set_object_id(this->CreatureStat->GetCreatureInfo()->object_info().object_id());

		SEND_PACKET(message::HEADER::ASSASSIN_Q_REQ, skillPkt);
	}
}

void ANJK1Assassin::SpawnDagger(FVector SpawnPoint, FRotator SpawnRotation)
{
	Super::SpawnDagger(SpawnPoint, SpawnRotation);
}

void ANJK1Assassin::SkillQTrace()
{
	FVector Start = GetActorLocation() + SpawnLocation;
	FVector End = Start + (GetActorForwardVector() * 1000.f); // 1000 유닛 앞까지 트레이스

	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	bool bHit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		Start,
		End,
		CCHANNEL_JK1ACTION,
		CollisionParams
	);
	if (bHit)
	{
		DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 3, 0, 3);
		UE_LOG(LogTemp, Warning, TEXT("Pawn Hit: %s"), *HitResult.GetActor()->GetName());

		if (auto* Actor = Cast<AJK1CreatureBase>(HitResult.GetActor()))
		{
			uint32 my_id = this->CreatureStat->GetCreatureInfo()->object_info().object_id();
			uint32 target_id = Actor->CreatureStat->GetCreatureInfo()->object_info().object_id();

			message::C_Attack pkt;
			pkt.set_object_id(my_id);
			pkt.add_target_ids(target_id);
			pkt.set_damage(15.f);

			SEND_PACKET(message::HEADER::PLAYER_ATTACK_REQ, pkt);
		}

	}
	else
	{
		DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 3, 0, 3);
	}
}

void ANJK1Assassin::OnHit(AActor* Actor, FHitResult& HitResult)
{
	if (Actor)
	{
		FVector HitLocation = HitResult.ImpactPoint;
		FVector ForwardVector = GetActorForwardVector();
		FVector OtherForwardVector = Actor->GetActorForwardVector();

		if (FVector::DotProduct(ForwardVector, OtherForwardVector) > 0)
		{
			if (HitEffect)
			{
				//TODO : 데미지 증가
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, HitLocation);
			}
		}
	}
}

void ANJK1Assassin::SpawnHitEffect(const FVector& Location)
{
	if (HitEffect)
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, Location);
}

void ANJK1Assassin::SkillR(const FInputActionValue& Value)
{
	if (isMyPlayer)
	{
		skill::C_ASSASSIN_R skillPkt;
		skillPkt.set_object_id(this->CreatureStat->GetCreatureInfo()->object_info().object_id());

		SEND_PACKET(message::HEADER::ASSASSIN_R_REQ, skillPkt);
	}
}

void ANJK1Assassin::SkillLShift(const FInputActionValue& Value)
{
	if (isMyPlayer)
	{
		skill::C_ASSASSIN_LS skillPkt;
		skillPkt.set_object_id(this->CreatureStat->GetCreatureInfo()->object_info().object_id());

		SEND_PACKET(message::HEADER::ASSASSIN_LS_REQ, skillPkt);
	}
}

void ANJK1Assassin::OnAttackHit(TArray<FHitResult> attackHits)
{
	message::C_Attack pkt;
	uint32 my_id = this->CreatureStat->GetCreatureInfo()->object_info().object_id();
	pkt.set_object_id(my_id);

	for (FHitResult& hit : attackHits)
	{

		AActor* actor = hit.GetActor();
		if (auto* Actor = Cast<AJK1CreatureBase>(actor))
		{
			uint32 target_id = Actor->CreatureStat->GetCreatureInfo()->object_info().object_id();


			if (IsBackAttack(actor, hit))
			{
				// 백어택 데미지
				message::C_Attack backAttackPkt;
				backAttackPkt.set_object_id(my_id);
				backAttackPkt.set_damage(21.f);
				backAttackPkt.add_target_ids(target_id);
				//SEND_PACKET(message::HEADER::PLAYER_ATTACK_REQ, backAttackPkt);
			}
			if (IsBackAttack(actor, hit))
			{
				// 백어택 이펙트
				FVector HitLocation = hit.ImpactPoint;
				skill::C_Assassin_E ePkt;
				ePkt.set_object_id(my_id);
				ePkt.set_x(HitLocation.X);
				ePkt.set_y(HitLocation.Y);
				ePkt.set_z(HitLocation.Z);

				SEND_PACKET(message::HEADER::ASSASSIN_E_REQ, ePkt);
				continue;
			}
			else
			{
				pkt.set_damage(13.f);
			}

			pkt.add_target_ids(target_id);
		}
	}
	SEND_PACKET(message::HEADER::PLAYER_ATTACK_REQ, pkt);
}

void ANJK1Assassin::OnAssassinQ_Hit(FHitResult hit)
{
	if (auto* Actor = Cast<AJK1CreatureBase>(hit.GetActor()))
{
		uint32 my_id = this->CreatureStat->GetCreatureInfo()->object_info().object_id();
		uint32 target_id = Actor->CreatureStat->GetCreatureInfo()->object_info().object_id();

		message::C_Attack pkt;
		pkt.set_object_id(my_id);
		pkt.add_target_ids(target_id);
		pkt.set_damage(15.f);

		SEND_PACKET(message::HEADER::PLAYER_ATTACK_REQ, pkt);
	}
}

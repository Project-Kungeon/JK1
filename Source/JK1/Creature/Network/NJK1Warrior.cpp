// Copyright 2024 All Rights Reserved by J&K


#include "Creature/Network/NJK1Warrior.h"
#include "Creature/JK1CreatureStatComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ANJK1Warrior::ANJK1Warrior()
	: Super()
{

}

ANJK1Warrior::~ANJK1Warrior()
{
	delete PlayerInfo;
	delete DestInfo;
	PlayerInfo = nullptr;
	DestInfo = nullptr;
}

void ANJK1Warrior::BeginPlay()
{
	Super::BeginPlay();
	// Set size for collision capsule
	{
		FVector Location = GetActorLocation();
		FRotator Rotator = GetActorRotation();

		DestInfo->set_x(Location.X);
		DestInfo->set_y(Location.Y);
		DestInfo->set_z(Location.Z);
		DestInfo->set_yaw(Rotator.Yaw);
		DestInfo->set_pitch(Rotator.Pitch);
		DestInfo->set_roll(Rotator.Roll);

		SetMoveState(message::MOVE_STATE_IDLE);
	}
}

void ANJK1Warrior::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANJK1Warrior::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ANJK1Warrior::Move(const FInputActionValue& Value)
{
	Super::Move(Value);
	/*FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, MovementVector.X);
	AddMovementInput(RightDirection, MovementVector.Y);*/
}

void ANJK1Warrior::Look(const FInputActionValue& Value)
{
	Super::Look(Value);
}

void ANJK1Warrior::Attack()
{
	Super::Attack();
	if (isMyPlayer)
	{
		skill::C_Warrior_Attack attcakPkt;
		attcakPkt.set_object_id(this->CreatureStat->GetCreatureInfo()->object_info().object_id());
		
		SEND_PACKET(message::HEADER::WARRIOR_ATTACK_REQ, attcakPkt);
	}
	
}

void ANJK1Warrior::OnBasicAttackHit(TArray<FHitResult> HitResults)
{
	if (!HitResults.IsEmpty())
	{
		if (bParryActive)
		{
			// 패링했을 때
			skill::C_Warrior_E_Success pkt;
			for (FHitResult& hit : HitResults)
			{
				AActor* actor = hit.GetActor();
				uint32 my_id = this->CreatureStat->GetCreatureInfo()->object_info().object_id();
				pkt.set_object_id(my_id);

				if (auto* Actor = Cast<AJK1CreatureBase>(actor))
				{
					uint32 target_id = Actor->CreatureStat->GetCreatureInfo()->object_info().object_id();
					pkt.set_target_id(target_id);

					SEND_PACKET(message::HEADER::WARRIOR_E_SUCCESS_REQ, pkt);
					break;
				}
			}
		}
		else
		{
			// 기본 공격
			message::C_Attack pkt;
			for (FHitResult& hit : HitResults)
			{
				AActor* actor = hit.GetActor();
				uint32 my_id = this->CreatureStat->GetCreatureInfo()->object_info().object_id();
				pkt.set_object_id(my_id);
				pkt.set_damage(10.f);

				if (auto* Actor = Cast<AJK1CreatureBase>(actor))
				{
					uint32 target_id = Actor->CreatureStat->GetCreatureInfo()->object_info().object_id();
					pkt.add_target_ids(target_id);
					SEND_PACKET(message::HEADER::PLAYER_ATTACK_REQ, pkt);
				}
			}
		}
		
	}
	/*if (!parryHits.IsEmpty())
	{
		for (FHitResult& hit : parryHits)
		{
			AActor* actor = hit.GetActor();
			if (auto* Actor = Cast<AJK1CreatureBase>(actor))
			{
				uint32 my_id = this->CreatureStat->GetCreatureInfo()->object_info().object_id();
				uint32 target_id = Actor->CreatureStat->GetCreatureInfo()->object_info().object_id();

				message::C_Attack pkt;
				pkt.set_object_id(my_id);
				pkt.add_target_ids(target_id);
				pkt.set_damage(20.f);

				SEND_PACKET(message::HEADER::PLAYER_ATTACK_REQ, pkt);
			}
		}
	}*/
}

void ANJK1Warrior::ComboActionBegin()
{
	Super::ComboActionBegin();
}

void ANJK1Warrior::DoCombo()
{
	Super::DoCombo();
}

void ANJK1Warrior::ComboActionEnd()
{
	Super::ComboActionEnd();
}

void ANJK1Warrior::SkillQ(const FInputActionValue& Value)
{
	//Super::SkillQ(Value);
	if (isMyPlayer)
	{
		skill::C_Warrior_Q skillPkt;
		skillPkt.set_object_id(this->CreatureStat->GetCreatureInfo()->object_info().object_id());

		SEND_PACKET(message::HEADER::WARRIOR_Q_REQ, skillPkt);
	}
}

void ANJK1Warrior::SkillE(const FInputActionValue& Value)
{
	//Super::SkillE(Value);
	if (isMyPlayer)
	{
		skill::C_Warrior_E skillPkt;
		skillPkt.set_object_id(this->CreatureStat->GetCreatureInfo()->object_info().object_id());

		SEND_PACKET(message::HEADER::WARRIOR_E_REQ, skillPkt);
	}
}

void ANJK1Warrior::SkillR(const FInputActionValue& Value)
{
	//Super::SkillR(Value);
	if (isMyPlayer)
	{
		skill::C_Warrior_R skillPkt;
		skillPkt.set_object_id(this->CreatureStat->GetCreatureInfo()->object_info().object_id());

		SEND_PACKET(message::HEADER::WARRIOR_R_REQ, skillPkt);
	}
}

void ANJK1Warrior::SkillLShift(const FInputActionValue& Value)
{
	//Super::SkillLShift(Value);
	if (isMyPlayer)
	{
		skill::C_Warrior_LS skillPkt;
		skillPkt.set_object_id(this->CreatureStat->GetCreatureInfo()->object_info().object_id());
		FVector ForwardDirection = GetActorForwardVector();
		skillPkt.set_x(ForwardDirection.X);
		skillPkt.set_y(ForwardDirection.Y);
		skillPkt.set_z(ForwardDirection.Z);

		SEND_PACKET(message::HEADER::WARRIOR_LS_REQ, skillPkt);
	}
}

void ANJK1Warrior::CheckDamagedInParry()
{
	if (bParryActive)
	{
		// TODO : 패링 성공 시 호출
		skill::C_Warrior_E_Success skillPkt;
		skillPkt.set_object_id(this->CreatureStat->GetCreatureInfo()->object_info().object_id());

		// 패링 성공 시, 상대 피격은 아직 구현되지 않았기에 Temp로 남겨둠
		skillPkt.set_target_id(0);
		SEND_PACKET(message::HEADER::WARRIOR_E_SUCCESS_REQ, skillPkt);

		WarriorE_Success();
	}
}

void ANJK1Warrior::DealDamageOverTime()
{
	// 남은 시간이 있다면 데미지를 적용
	if (RemainingDamageTime > 0)
	{
		TArray<FOverlapResult> rHits;
		rHits = CheckSkillRTrace();
		if (!rHits.IsEmpty())
		{
			message::C_Attack pkt;
			uint32 my_id = this->CreatureStat->GetCreatureInfo()->object_info().object_id();
			pkt.set_object_id(my_id);
			pkt.set_damage(2.f);
			for (FOverlapResult& hit : rHits)
			{
				AActor* actor = hit.GetActor();
				if (auto* Actor = Cast<AJK1CreatureBase>(actor))
				{
					uint32 target_id = Actor->CreatureStat->GetCreatureInfo()->object_info().object_id();
					pkt.add_target_ids(target_id);
				}
			}
			SEND_PACKET(message::HEADER::PLAYER_ATTACK_REQ, pkt);
		}

		RemainingDamageTime -= DamageInterval;

		// 남은 시간이 0 이하가 되면 타이머 중지
		if (RemainingDamageTime <= 0)
		{
			GetWorldTimerManager().ClearTimer(DamageTimerHandle);
			ResetSkillCooldown();
		}
	}
}

void ANJK1Warrior::StartROverTime()
{
	TArray<FOverlapResult> rHits;
	// 총 데미지 지속 시간 초기화
	RemainingDamageTime = DamageDuration;

	GetWorldTimerManager().SetTimer(DamageTimerHandle, this, &ANJK1Warrior::DealDamageOverTime, DamageInterval, true);
}

// Copyright 2024 All Rights Reserved by J&K


#include "Creature/Network/NJK1Archor.h"
#include "Creature/JK1CreatureStatComponent.h"

ANJK1Archor::ANJK1Archor()
	: AJK1Archor()
{
}

ANJK1Archor::~ANJK1Archor()
{
	delete PlayerInfo;
	delete DestInfo;
	PlayerInfo = nullptr;
	DestInfo = nullptr;
}

void ANJK1Archor::BeginPlay()
{
	Super::BeginPlay();
}

void ANJK1Archor::Tick(float DeltaTime)
{
	AJK1PlayerCharacter::Tick(DeltaTime);
}

void ANJK1Archor::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ANJK1Archor::DoCombo()
{
	FVector ShootPoint = GetMesh()->GetSocketLocation(FName(TEXT("BowEmitterSocket")));

	//Super::DoCombo();
	switch (CurrentCombo)
	{
	case 0:
		if (isMyPlayer)
		{
			skill::C_Archor_Attack attackPkt;
			attackPkt.set_object_id(this->CreatureStat->GetCreatureInfo()->object_info().object_id());
			if (GetWorld())
			{
				APlayerCameraManager* CameraManager = Cast<APlayerCameraManager>(UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0));
				FVector ArrowStartLoc = GetStartArrowLoc(CameraManager);
				FVector ArrowEndLoc = GetEndArrowLoc(CameraManager);

				attackPkt.set_start_x(ArrowStartLoc.X);
				attackPkt.set_start_y(ArrowStartLoc.Y);
				attackPkt.set_start_z(ArrowStartLoc.Z);
				attackPkt.set_end_x(ArrowEndLoc.X);
				attackPkt.set_end_y(ArrowEndLoc.Y);
				attackPkt.set_end_z(ArrowEndLoc.Z);

				SEND_PACKET(message::HEADER::ARCHOR_ATTACK_REQ, attackPkt);
				ArchorAttack(ArrowStartLoc, ArrowEndLoc);
			}
			
		}
		
		break;
	}
}

void ANJK1Archor::OnBasicAttackHit(TArray<FHitResult> HitResults)
{
	if (isMyPlayer)
	{
		// Create Attack Pkt
		message::C_Attack pkt;
		uint32 my_id = this->CreatureStat->GetCreatureInfo()->object_info().object_id();
		pkt.set_object_id(my_id);

		for (auto& hit : HitResults)
		{
			AActor* actor = hit.GetActor();
			if (auto* Actor = Cast<AJK1CreatureBase>(actor))
			{
				uint32 target_id = Actor->CreatureStat->GetCreatureInfo()->object_info().object_id();
				pkt.add_target_ids(target_id);
			}
		}
		if (IsLShift)
		{
			pkt.set_damage(10);
		}
		else
		{
			pkt.set_damage(5);
		}

		SEND_PACKET(message::HEADER::PLAYER_ATTACK_REQ, pkt);
	}
}

void ANJK1Archor::SkillQ(const FInputActionValue& value)
{
	if (isMyPlayer)
	{
		skill::C_Archor_Q_Charging skillPkt;
		skillPkt.set_object_id(this->CreatureStat->GetCreatureInfo()->object_info().object_id());

		SEND_PACKET(message::HEADER::ARCHOR_Q_CHARGING_REQ, skillPkt);
	}
}

void ANJK1Archor::SkillE(const FInputActionValue& value)
{
	if (isMyPlayer)
	{
		skill::C_Archor_E skillPkt;
		skillPkt.set_object_id(this->CreatureStat->GetCreatureInfo()->object_info().object_id());
		FVector E_Loc = CalculateDamageLocation();
		skillPkt.set_x(E_Loc.X);
		skillPkt.set_y(E_Loc.Y);
		skillPkt.set_z(E_Loc.Z);

		SEND_PACKET(message::HEADER::ARCHOR_E_REQ, skillPkt);
	}
}

void ANJK1Archor::SkillR(const FInputActionValue& value)
{
	if (isMyPlayer)
	{
		skill::C_Archor_R skillPkt;
		skillPkt.set_object_id(this->CreatureStat->GetCreatureInfo()->object_info().object_id());

		SEND_PACKET(message::HEADER::ARCHOR_R_REQ, skillPkt);
	}
}

void ANJK1Archor::SkillLShift(const FInputActionValue& value)
{
	if (isMyPlayer)
	{
		skill::C_Archor_LS skillPkt;
		skillPkt.set_object_id(this->CreatureStat->GetCreatureInfo()->object_info().object_id());

		SEND_PACKET(message::HEADER::ARCHOR_LS_REQ, skillPkt);
	}
}

void ANJK1Archor::OnArchorQ_Hit(FHitResult hit)
{
	if (isMyPlayer)
	{
		// Create Attack Pkt
		message::C_Attack pkt;
		uint32 my_id = this->CreatureStat->GetCreatureInfo()->object_info().object_id();
		pkt.set_object_id(my_id);
		AActor* actor = hit.GetActor();
		if (auto* Actor = Cast<AJK1CreatureBase>(actor))
		{
			uint32 target_id = Actor->CreatureStat->GetCreatureInfo()->object_info().object_id();
			pkt.add_target_ids(target_id);
		}

		else
		{
			pkt.set_damage(15);
		}

		SEND_PACKET(message::HEADER::PLAYER_ATTACK_REQ, pkt);
	}
}

void ANJK1Archor::OnArchorE_Hit(TArray<FHitResult> hits)
{
	if (isMyPlayer)
	{
		message::C_Attack pkt;
		uint32 my_id = this->CreatureStat->GetCreatureInfo()->object_info().object_id();
		pkt.set_object_id(my_id);
		pkt.set_damage(2);
		for (FHitResult& hit : hits)
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
}

void ANJK1Archor::ShootNRecovery()
{
	if (GetWorld() && isMyPlayer)
	{
		APlayerCameraManager* CameraManager = Cast<APlayerCameraManager>(UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0));
		
		skill::C_Archor_Q_Shot skillPkt;
		skillPkt.set_object_id(this->CreatureStat->GetCreatureInfo()->object_info().object_id());
		FVector ArrowStartLoc = GetStartArrowLoc(CameraManager);
		FVector ArrowEndLoc = GetEndArrowLoc(CameraManager);

		skillPkt.set_start_x(ArrowStartLoc.X);
		skillPkt.set_start_y(ArrowStartLoc.Y);
		skillPkt.set_start_z(ArrowStartLoc.Z);
		skillPkt.set_end_x(ArrowEndLoc.X);
		skillPkt.set_end_y(ArrowEndLoc.Y);
		skillPkt.set_end_z(ArrowEndLoc.Z);

		SEND_PACKET(message::HEADER::ARCHOR_Q_SHOT_REQ, skillPkt);

	}
}

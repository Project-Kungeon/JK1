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
	AJK1PlayerCharacter::Tick(DeltaTime);
	TArray<FHitResult> hits;
	if (bWeaponActive)
		hits = CheckWeaponTrace();

	if (!hits.IsEmpty())
	{
		for (FHitResult& hit : hits)
		{
			AActor* actor = hit.GetActor();
			if (auto* Actor = Cast<AJK1CreatureBase>(actor))
			{
				uint32 my_id = this->CreatureStat->GetCreatureInfo()->object_info().object_id();
				uint32 target_id = Actor->CreatureStat->GetCreatureInfo()->object_info().object_id();

				message::C_Attack pkt;
				pkt.set_object_id(my_id);
				pkt.add_target_ids(target_id);
				pkt.set_damage(1.f);

				SEND_PACKET(message::HEADER::PLAYER_ATTACK_REQ, pkt);
			}
		}
	}

	if (isMyPlayer)
	{
		/*----- 다른 방안 알아보기 -----*/
		if (!DashVelocity.IsZero())
		{
			FVector NewLocation = GetActorLocation() + (DashVelocity * DeltaTime);
			SetActorLocation(NewLocation);
		}
	}
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
	Super::SkillQ(Value);
}

void ANJK1Warrior::SkillE(const FInputActionValue& Value)
{
	Super::SkillE(Value);
	if (isMyPlayer)
	{
		skill::C_Warrior_E skillPkt;
		skillPkt.set_object_id(this->CreatureStat->GetCreatureInfo()->object_info().object_id());

		SEND_PACKET(message::HEADER::WARRIOR_E_REQ, skillPkt);
	}
}

void ANJK1Warrior::SkillR(const FInputActionValue& Value)
{
	Super::SkillR(Value);
	if (isMyPlayer)
	{
		skill::C_Warrior_R skillPkt;
		skillPkt.set_object_id(this->CreatureStat->GetCreatureInfo()->object_info().object_id());

		SEND_PACKET(message::HEADER::WARRIOR_R_REQ, skillPkt);
	}
}

void ANJK1Warrior::SkillLShift(const FInputActionValue& Value)
{
	Super::SkillLShift(Value);
}
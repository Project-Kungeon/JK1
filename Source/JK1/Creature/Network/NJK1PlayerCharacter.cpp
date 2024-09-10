// Copyright 2024 All Rights Reserved by J&K

#include "NJK1PlayerCharacter.h"
#include "Creature/JK1CreatureStatComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ANJK1PlayerCharacter::ANJK1PlayerCharacter()
	: Super()
{
	PlayerInfo = new message::PosInfo();
	DestInfo = new message::PosInfo();

	CreatureStat->SetOwner(true, FName("Warrior"));
}

ANJK1PlayerCharacter::~ANJK1PlayerCharacter()
{
	delete PlayerInfo;
	delete DestInfo;
	PlayerInfo = nullptr;
	DestInfo = nullptr;
}

void ANJK1PlayerCharacter::BeginPlay()
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

void ANJK1PlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	{
		FVector Location = GetActorLocation();
		PlayerInfo->set_x(Location.X);
		PlayerInfo->set_y(Location.Y);
		PlayerInfo->set_z(Location.Z);
		PlayerInfo->set_yaw(GetControlRotation().Yaw);
	}

	if (isMyPlayer)
	{
		// Send Packet
		bool ForceSendPacket = false;	// 상태검사 결과에 따라 패킷 전송할지 말지 판단합니다.

		if (LastDesiredInput != DesiredInput)
		{
			// 움직였다면, 패킷 전송을 합니다.
			ForceSendPacket = true;
			LastDesiredInput = DesiredInput;
		}

		if ((DesiredInput.X == 0 && DesiredInput.Y == 0) || GetVelocity().IsNearlyZero())
		{
			SetMoveState(message::MOVE_STATE_IDLE);
		}

		else
			SetMoveState(message::MOVE_STATE_RUN);

		// 패킷 전송 주기 계산
		MovePacketSendTimer -= DeltaTime;

		if ((MovePacketSendTimer >= 0 || ForceSendPacket) && isConnected)
		{
			MovePacketSendTimer = MOVE_PACKET_SEND_DELAY;
			message::C_Move	MovePkt;

			{
				message::PosInfo* info = MovePkt.mutable_posinfo();
				info->CopyFrom(*PlayerInfo);
				info->set_yaw(DesiredYaw);
				info->set_state(GetMoveState());
			}
			// TODO : Send Packet should be needed
			// Will Test...
			SEND_PACKET(message::HEADER::PLAYER_MOVE_REQ, MovePkt);
		}
	}

	else
	{
		const message::MoveState State = GetMoveState();

		if (State == message::MOVE_STATE_RUN)	// 뛰는 중이라면
		{
			SetActorRotation(FRotator(0, DestInfo->yaw(), 0));
			AddMovementInput(GetActorForwardVector());

			FVector vec(DestInfo->x(), DestInfo->y(), DestInfo->z());
			SetActorLocation(vec);

		}
		else if (State == message::MOVE_STATE_IDLE)
		{

			const FRotator YawRotation(0, DestInfo->yaw(), 0);

			const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

			AddMovementInput(ForwardDirection, 0);
			AddMovementInput(RightDirection, 0);
		}
		else
		{

		}
	}
}

void ANJK1PlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ANJK1PlayerCharacter::Move(const FInputActionValue& Value)
{
	Super::Move(Value);
	FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, MovementVector.X);
	AddMovementInput(RightDirection, MovementVector.Y);

	if (isMyPlayer)
	{
		DesiredInput = MovementVector;

		DesiredMoveDirection = FVector::ZeroVector;
		DesiredMoveDirection += ForwardDirection * MovementVector.Y;
		DesiredMoveDirection += RightDirection * MovementVector.X;
		DesiredMoveDirection.Normalize();

		const FVector Location = GetActorLocation();

		FRotator Rotator = UKismetMathLibrary::FindLookAtRotation(Location, Location + DesiredMoveDirection);
		DesiredYaw = Rotator.Yaw;
	}
}

void ANJK1PlayerCharacter::Look(const FInputActionValue& Value)
{
	Super::Look(Value);
}

void ANJK1PlayerCharacter::Attack()
{
	Super::Attack();
}

void ANJK1PlayerCharacter::ComboActionBegin()
{
	Super::ComboActionBegin();
}

void ANJK1PlayerCharacter::DoCombo()
{
	Super::DoCombo();
}

void ANJK1PlayerCharacter::ComboActionEnd()
{
	Super::ComboActionEnd();
}

void ANJK1PlayerCharacter::SkillQ(const FInputActionValue& Value)
{
	Super::SkillQ(Value);
}

void ANJK1PlayerCharacter::SkillE(const FInputActionValue& Value)
{
	Super::SkillE(Value);
}

void ANJK1PlayerCharacter::SkillR(const FInputActionValue& Value)
{
	Super::SkillR(Value);
}

void ANJK1PlayerCharacter::SkillLShift(const FInputActionValue& Value)
{
	Super::SkillLShift(Value);
}

void ANJK1PlayerCharacter::SetMoveState(message::MoveState State)
{
	// 기존 상태와 같다면 스킵합니다.
	if (PlayerInfo->state() == State)
		return;

	PlayerInfo->set_state(State);
}

void ANJK1PlayerCharacter::SetPlayerInfo(const message::PosInfo& Info)
{
	if (PlayerInfo->object_id() != 0)
		return;
	PlayerInfo->CopyFrom(Info);

	// 위치 동기화
	FVector Location(Info.x(), Info.y(), Info.z());
	SetActorLocation(Location);
}

void ANJK1PlayerCharacter::SetDestInfo(const message::PosInfo& Info)
{
	if (PlayerInfo->object_id() != 0)
	{
		assert(PlayerInfo->object_id() == Info.object_id());
	}

	// 위치 동기화
	//FVector TargetLocation(Info.x(), Info.y(), Info.z());
	//FVector MoveDirection = TargetLocation - GetActorLocation();
	//MoveDirection.Normalize();
	//GetCharacterMovement()->AddInputVector(MoveDirection);

	// 위치 정보 갱신
	DestInfo->CopyFrom(Info);
	SetMoveState(Info.state());
}



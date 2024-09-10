// Copyright 2024 All Rights Reserved by J&K

#pragma once

#include "CoreMinimal.h"
#include "Creature/PC/JK1PlayerCharacter.h"
#include "JK1.h"
#include "Kismet/KismetMathLibrary.h"
#include "NJK1PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class JK1_API ANJK1PlayerCharacter : public AJK1PlayerCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANJK1PlayerCharacter();
	virtual ~ANJK1PlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	//Move and Look Function
	virtual void Move(const FInputActionValue& Value) override;
	virtual void Look(const FInputActionValue& Value) override;

	//Attack Function
	virtual void Attack();

	virtual void ComboActionBegin() override;
	virtual void DoCombo() override;
	virtual void ComboActionEnd() override;

	//Skill 
	virtual void SkillQ(const FInputActionValue& Value) override;
	virtual void SkillE(const FInputActionValue& Value) override;
	virtual void SkillR(const FInputActionValue& Value) override;
	virtual void SkillLShift(const FInputActionValue& Value) override;

	/*
	 * Network Module
	 */
public:

	// Only My Player
	bool isConnected = false;
	// ======================

	message::MoveState GetMoveState() { return PlayerInfo->state(); }
	void SetMoveState(message::MoveState State);

public:
	void SetPlayerInfo(const message::PosInfo& Info);
	void SetDestInfo(const message::PosInfo& Info);
	message::PosInfo* GetPlayerInfo() { return PlayerInfo; }



protected:
	// Relate Network...
	class message::PosInfo* PlayerInfo;		// 플레이어 정보
	class message::PosInfo* DestInfo;		// 목적지 정보 -> 이동 동기화

	// Only My Player
	// 패킷 전송 주기(Pakcet Sending Delay)
	const float MOVE_PACKET_SEND_DELAY = 0.1f;
	float MovePacketSendTimer = MOVE_PACKET_SEND_DELAY;

	// Position Cache (이 값으로 이동 여부 판단)
	FVector2D DesiredInput;
	FVector DesiredMoveDirection;
	float DesiredYaw;

	// Dirty Flag Test (이동 상태 검사)
	FVector2D LastDesiredInput;
	// ======================
};

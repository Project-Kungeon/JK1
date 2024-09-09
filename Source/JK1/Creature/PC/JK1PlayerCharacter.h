// Copyright 2024 All Rights Reserved by J&K

#pragma once

#include "CoreMinimal.h"
#include "../JK1CreatureBase.h"
#include "InputActionValue.h"
#include "Kismet/KismetMathLibrary.h"
#include "JK1PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class JK1_API AJK1PlayerCharacter : public AJK1CreatureBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AJK1PlayerCharacter();
	virtual ~AJK1PlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	/*
	* Member Function
	*/
public:
	//Move and Look 
	virtual void Move(const FInputActionValue& Value);
	virtual void Look(const FInputActionValue& Value);

	//Attack 
	virtual void Attack();

	UFUNCTION(BlueprintCallable)
	virtual void ComboActionBegin();
	UFUNCTION(BlueprintCallable)
	virtual void DoCombo();
	UFUNCTION(BlueprintCallable)
	virtual void ComboActionEnd();

	//Skill 
	virtual void SkillQ(const FInputActionValue& Value);
	virtual void SkillE(const FInputActionValue& Value);
	virtual void SkillR(const FInputActionValue& Value);
	virtual void SkillLShift(const FInputActionValue& Value);

	virtual void Death() override;

	/*
	* Member Variable
	*/
protected:
	UPROPERTY(EditAnywhere, Category = "Camera")
	TObjectPtr<class USpringArmComponent> CameraBoom;

	UPROPERTY(EditAnywhere, Category = "Camera")
	TObjectPtr<class UCameraComponent> FollowCamera;

	class AJK1PlayerController* PlayerController;

public:
	UPROPERTY(BlueprintReadWrite)
	bool bWeaponActive;

	/* Ÿ�ֿ̹� �°� �Է��ϴ� �и����� ���� */
	UPROPERTY(BlueprintReadWrite)
	bool bParryActive = false;

	UPROPERTY()
	TSet<AActor*> WeaponAttackTargets;

	// combo == 0 not start 
	// combo >= 1 -> Combo Start
	int32 CurrentCombo = 0;
	uint8 IsAttacking : 1;
	uint8 SaveAttacking : 1;
	int32 MaxCombo;



public:
	bool isMyPlayer = false;

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

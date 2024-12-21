// Copyright 2024 All Rights Reserved by J&K

#pragma once

#include "CoreMinimal.h"
#include "../JK1CreatureBase.h"
#include "InputActionValue.h"
#include "Kismet/KismetMathLibrary.h"
#include "JK1PlayerCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnResurrectionDelegate);
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

	//Combo
	UFUNCTION(BlueprintCallable)
	virtual void ComboActionBegin();
	UFUNCTION(BlueprintCallable)
	virtual void DoCombo();
	UFUNCTION(BlueprintCallable)
	virtual void ComboActionEnd();
	virtual void	OnBasicAttackHit(TArray<FHitResult> HitResults);

	//Skill 
	virtual void SkillQ(const FInputActionValue& Value);
	virtual void SkillE(const FInputActionValue& Value);
	virtual void SkillR(const FInputActionValue& Value);
	virtual void SkillLShift(const FInputActionValue& Value);

	virtual void Death() override;

	UFUNCTION(BlueprintCallable)
	void Resurrection();

	//Skill Cooldown Time Getter Setter func
	float GetQ() { return SkillQCool; }
	float GetE() { return SkillECool; }
	float GetR() { return SkillRCool; }
	float GetLS() { return SkillLSCool; }

	void SetQ(float Q) { SkillQCool = Q; }
	void SetE(float E) { SkillECool = E; }
	void SetR(float R) { SkillRCool = R; }
	void SetLS(float LS) { SkillLSCool = LS; }

	virtual void StartQTimer();
	virtual void StartETimer();
	virtual void StartRTimer();
	virtual void StartLSTimer();


	/*
	* Member Variable
	*/

protected:
	UPROPERTY(EditAnywhere, Category = "Camera")
	TObjectPtr<class USpringArmComponent> CameraBoom;

	UPROPERTY(EditAnywhere, Category = "Camera")
	TObjectPtr<class UCameraComponent> FollowCamera;

	// Check Montage AnimInstance
	UAnimInstance* AnimInstance = nullptr;

	class AJK1PlayerController* PlayerController;
	class AJK1DemoRaidState* DemoRaidState;

public:
	// Delegate
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnResurrectionDelegate OnResurrection;

	//Cooldown Timer handle
	FTimerHandle Qhandler;
	FTimerHandle QBuffHandler;
	FTimerHandle Ehandler;
	FTimerHandle Rhandler;
	FTimerHandle RBuffHandler;
	FTimerHandle LShandler;
	FTimerHandle LSBuffHandler;

	//Check Skill Cooldown Var
	UPROPERTY(BlueprintReadOnly)
	float SkillQCool;
	UPROPERTY(BlueprintReadOnly)
	float SkillECool;
	UPROPERTY(BlueprintReadOnly)
	float SkillRCool;
	UPROPERTY(BlueprintReadOnly)
	float SkillLSCool;

	//Check BuffCooldown Var
	UPROPERTY(BlueprintReadOnly)
	float QLeftTime = 0.f;
	UPROPERTY(BlueprintReadOnly)
	float RLeftTime = 0.f;
	UPROPERTY(BlueprintReadOnly)
	float LSLeftTime = 0.f;

	UPROPERTY(BlueprintReadWrite)
	bool bWeaponActive;


	/* 타이밍에 맞게 입력하는 패링으로 수정 */
	UPROPERTY(BlueprintReadWrite)
	bool bParryActive = false;

	UPROPERTY()
	TSet<AActor*> WeaponAttackTargets;

	// rigid Immunity Skill Montage name
	UPROPERTY(BlueprintReadWrite)
	TArray<FString> RISkills;

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
	void SetMoveInfo(const message::S_Move& info);
	message::PosInfo* GetPlayerInfo() { return PlayerInfo; }



protected:
	// Relate Network...
	class message::PosInfo* PlayerInfo;		// 플레이어 정보
	class message::PosInfo* DestInfo;		// 목적지 정보 -> 이동 동기화
	// 타 플레이어의 yaw값 동기화
	float sync_camera_yaw;
	float sync_controller_yaw;
	double movement_x;
	double movement_y;

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

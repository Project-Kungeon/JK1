// Copyright 2024 All Rights Reserved by J&K

#pragma once

#include "CoreMinimal.h"
#include "../JK1PlayerCharacter.h"
#include "JK1Archor.generated.h"

/**
 * 
 */
UCLASS()
class JK1_API AJK1Archor : public AJK1PlayerCharacter
{
	GENERATED_BODY()
public:
	AJK1Archor();

protected:
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
protected:
	//Attack Funciton
	virtual void Attack() override;
	void Shoot();
	void SpawnArrow();
	void SpawnArrowCheck();

	//ComboAction
	virtual void ComboActionBegin() override;
	virtual void DoCombo() override;
	virtual void ComboActionEnd() override;

public:
	//Skill Function
	virtual void SkillQ(const FInputActionValue& value) override;
	virtual void SkillE(const FInputActionValue& value) override;
	virtual void SkillR(const FInputActionValue& value) override;
	virtual void SkillLShift(const FInputActionValue& value) override;

	void ShootNRecovery();
	void EndSkillR();
	void DealDamage();
	void StartDamage();
	void StopDamage();
	void CheckSkillETrace();
	void PlayParticleSystem();
	void StopParticleSystem();
	void BIsLShift() { IsLShift = false; }

	//SkillCooldownFunction
	virtual void StartQTimer() override;
	virtual void StartETimer() override;
	virtual void StartRTimer() override;
	virtual void StartLSTimer() override;



protected:
	//Montage, 클래스들은 각자 기본공격 몽타주 갯수가 다르다.
	//Archor는 활을 쏘는 모션 하나.

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<class UAnimMontage> ComboActionMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<class UAnimMontage> SkillQMonatge_Charge;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<class UAnimMontage> SkillQMonatge_Recovery;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<class UAnimMontage> SkillEMontage;

	UPROPERTY(EditAnywhere, Category = "Effects")
	TObjectPtr<class UParticleSystem> SkillEeffect;
	UPROPERTY(EditAnywhere, Category = "Effects")
	TObjectPtr<class UParticleSystem> SkillReffect;

	

	// 데미지량 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float DamagePerTick = 10.0f;
	// 데미지 처리 주기
	const float DamageInterval = 0.5f;
	// 타격 거리
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float DamageDistance = 1500.0f;

	// 데미지 타이머 변수
	FTimerHandle DamageTimerHandle;

	//Archor 일반공격 발사 애니메이션 재생 속도
	float ComboActionMontagePlayRate = 1.0f;
	//Archor SKillQMontage 재생 속도
	float SkillQMontagePlayRate = 1.5f;
	//SkillR 차징 애니메이션 재생 속도
	float SkillRChargePlayRate = 2.f;
	// 총 데미지 지속 시간 동안 남은 시간
	float RemainingDamageTime = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	TSubclassOf<UUserWidget> WidgetClass;

private:
	// 타격 위치 계산
	FVector CalculateDamageLocation();

	//Skill E 이펙트 컴포넌트 변수
	UParticleSystemComponent* SkillEDamageEffectComponent;

	//Skill E 타격 Location
	FVector SkillELocation;

	//현재 LShift스킬을 사용했는지 판단하는 bool type 변수
	bool IsLShift = false;

	// 데미지 범위 (Sphere) 변수
	float DamageRadius = 500.0f;

	//Arrow BP
	FName ArrowBP;

	//Character Widget
	UUserWidget* CurrentWidget;

	/*
	* Arrow Spawn에 필요한 Parameter 변수들
	*/
	UBlueprint* ObjectToSpawn;
	FVector CrosshairWorldLocation;
	FRotator ArrowSpawnRotation;
	FActorSpawnParameters SpawnParams;
	FTimerHandle ArrowHandler;
	int32 MaxTime = 5;
	int32 CurrentTime = 0;
	FVector ArrowStartLocation;
	FVector ImpactPoint;

	const float ArchorQCT = 5.f;
	const float ArchorECT = 12.f;
	const float ArchorRCT = 20.f;
	const float ArchorLSCT = 15.f;
	
};

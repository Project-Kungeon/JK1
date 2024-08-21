// Copyright 2024 All Rights Reserved by J&K


#include "JK1Archor.h"
#include "JK1/Physics/JK1Collision.h"
#include "../../JK1CreatureStatComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Animation/AnimMontage.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

AJK1Archor::AJK1Archor()
{
	//Path of Arrow Actor Blueprint Class
	//해당 부분 C++ Class 로 전환
	path = TEXT("/Script/Engine.Blueprint'/Game/Blueprints/Creature/PC/Archor/BP_JK1Arrow.BP_JK1Arrow'");

	//Montage 상하체 미 분리때문에 발생하는 현상
	//GetCharacterMovement()->bOrientRotationToMovement = false;
	//bUseControllerRotationYaw = true;

	static ConstructorHelpers::FObjectFinder<UInputMappingContext> InputMappingContextRef(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Input/IMC_JK1.IMC_JK1'"));
	if (nullptr != InputMappingContextRef.Object)
	{
		DefaultMappingContext = InputMappingContextRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> DefaultMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonSparrow/Characters/Heroes/Sparrow/Meshes/Sparrow.Sparrow'"));
	if (nullptr != DefaultMesh.Object)
	{
		Super::GetMesh()->SetSkeletalMesh(DefaultMesh.Object);
	}

	//이렇게 해야 애니메이션이 두번 동작 안함
	GetCharacterMovement()->JumpZVelocity = 400.f;
	GetCharacterMovement()->AddForce(FVector(100.f, 0.f, 0.f));
	GetCharacterMovement()->AirControl = 1.f;

	//Camera Offset 처리
	CameraBoom->SocketOffset = FVector(0.f, 120.f, 75.f);
	

	CreatureStat->SetOwner(true, FName("Archor"));
}

void AJK1Archor::BeginPlay()
{
	Super::BeginPlay();
}

void AJK1Archor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AJK1Archor::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AJK1Archor::Attack()
{
	Super::Attack();
	
}

void AJK1Archor::Shoot()
{
	/*
	사격게임에서 하는 히트 스캔 방식을 사용했습니다.

	스캔을 하고 오브젝트가 탐지되면 거리를 계산해서 발사하는 방식으로

	1. UI(조준선)가 잇는 월드 위치->카메라의 중심
	*/
	FRotator ArrowSpawnRotation;
	UBlueprint* ObjectToSpawn = Cast<UBlueprint>(StaticLoadObject(UBlueprint::StaticClass(), nullptr, *path.ToString()));
	FActorSpawnParameters SpawnParams;

	//Skeletal mesh의 idle 상태에서 화살 촉이 있는 부분
	FVector ShootPoint = GetMesh()->GetSocketLocation(FName(TEXT("BowEmitterSocket")));
	FHitResult HitResult;

	//Location Of Camera(Line Trace start)
	FVector CrosshairWorldLocation;
	FVector EndLocation;
	FVector ImpactPoint;

	//TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	TEnumAsByte<EObjectTypeQuery> WorldStatic = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic);
	TEnumAsByte<EObjectTypeQuery> WorldDynamic = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic);
	FCollisionQueryParams Params(SCENE_QUERY_STAT(Attack), false, this);

	//Camera Info 가져오기.
	if (GetWorld())
	{
		APlayerCameraManager* CameraManager = Cast<APlayerCameraManager>(UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0));
		if (CameraManager)
		{
			CrosshairWorldLocation = CameraManager->GetCameraLocation();
			//카메라의 전방 벡터 가져오기.
			EndLocation = CameraManager->GetActorForwardVector();
			//scaling forward vector by 15,000, 추적의 끝 부분, Multifly Vector Size 15000
			EndLocation.X *= 15000;
			EndLocation.Y *= 15000;
			EndLocation.Z *= 15000;
			//탐지하고자 하는 끝부분, Impact Target Point
			ImpactPoint = CrosshairWorldLocation + EndLocation;
		}
	}

	bool bSuccess = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		CrosshairWorldLocation,
		ImpactPoint,
		CCHANNEL_JK1ACTION,
		Params
	);

	if (bSuccess)
	{
		if (HitResult.bBlockingHit)
		{
			ImpactPoint = HitResult.ImpactPoint;
			UE_LOG(LogArchor, Log, TEXT("%d, %d, %d"), ImpactPoint.X, ImpactPoint.Y, ImpactPoint.Z);
		}
		/*ArrowSpawnLocation = ShootPoint;
		ArrowSpawnRotation = (ImpactPoint - ArrowSpawnLocation).Rotation();*/
		ArrowSpawnRotation = (ImpactPoint - CrosshairWorldLocation).Rotation();
		GetWorld()->SpawnActor<AActor>(ObjectToSpawn->GeneratedClass, CrosshairWorldLocation, ArrowSpawnRotation, SpawnParams);
	}

	//화살 생성
	UE_LOG(LogArchor, Log, TEXT("%d %d %d"), )
	//GetWorld()->SpawnActor<AActor>(ObjectToSpawn->GeneratedClass, ArrowSpawnLocation, ArrowSpawnRotation, SpawnParams);

#if ENABLE_DRAW_DEBUG
	FVector Direction = ImpactPoint - CrosshairWorldLocation;
	FColor DrawColor = bSuccess ? FColor::Green : FColor::Red;
	FQuat QuatRotation = FQuat::FindBetweenNormals(FVector::UpVector, Direction.GetSafeNormal());

	DrawDebugLine(
		GetWorld(),
		CrosshairWorldLocation,
		ImpactPoint,
		DrawColor,
		false,
		3.f,
		0,
		3.f
	);

#endif
}

void AJK1Archor::ComboActionBegin()
{
	Super::ComboActionBegin();
}

void AJK1Archor::DoCombo()
{
	Super::DoCombo();
	switch (CurrentCombo)
	{
	case 0:
		CurrentCombo = 1;
		PlayAnimMontage(ComboActionMontage, ComboActionMontagePlayRate);
		Shoot();
		break;
	}
}

void AJK1Archor::ComboActionEnd()
{
	Super::ComboActionEnd();
}

void AJK1Archor::SkillQ(const FInputActionValue& value)
{
	Super::SkillQ(value);
	UE_LOG(LogArchor, Log, TEXT("This is %s"), *this->GetName());

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance)
	{
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
		PlayAnimMontage(SkillQMonatge_Charge, SkillRChargePlayRate);
		FTimerHandle ChargeHandler;
		GetWorldTimerManager().SetTimer(ChargeHandler, this, &AJK1Archor::ShootNRecovery, SkillQMontagePlayRate, false);
	}
	//TODO: 움직임 제어
	
}

void AJK1Archor::SkillE(const FInputActionValue& value)
{
	Super::SkillE(value);
	UE_LOG(LogArchor, Log, TEXT("This is %s"), *this->GetName());
}

void AJK1Archor::SkillR(const FInputActionValue& value)
{
	Super::SkillR(value);
	UE_LOG(LogArchor, Log, TEXT("This is %s"), *this->GetName());
	{
		ComboActionMontagePlayRate = 2.0f;
		SkillQMontagePlayRate = 0.2f;
		SkillRChargePlayRate = 5.0f;
	}
	//TODO: Timer로 Rate 변수 초기화
}

void AJK1Archor::SkillLShift(const FInputActionValue& value)
{
	Super::SkillLShift(value);
	UE_LOG(LogArchor, Log, TEXT("This is %s"), *this->GetName());	
}

void AJK1Archor::ShootNRecovery()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	Shoot();
	PlayAnimMontage(SkillQMonatge_Recovery);
}

void AJK1Archor::EndSkillR()
{
	ComboActionMontagePlayRate = 1.0f;
	SkillQMontagePlayRate = 1.5f;
	SkillRChargePlayRate = 2.f;
}

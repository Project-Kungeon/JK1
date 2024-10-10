// Copyright 2024 All Rights Reserved by J&K

#include "JK1PlayerCharacter.h"
#include "InputActionValue.h"
#include "CoreMinimal.h"
#include "JK1/Physics/JK1Collision.h"
#include "Creature/JK1CreatureStatComponent.h"
#include "JK1/Controller/Player/JK1PlayerController.h"
#include "JK1/Widget/JK1PlayerHUD.h"
#include "JK1/Creature/JK1CreatureStatComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "Animation/AnimMontage.h"
#include "GameMode/DemoRaid/JK1DemoRaidState.h"

AJK1PlayerCharacter::AJK1PlayerCharacter()
	: Super()
{
	PrimaryActorTick.bCanEverTick = true;

	//Pawn
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	//Capsule (프로파일 설정)
	GetCapsuleComponent()->SetCollisionProfileName(CPROFILE_JK1CAPSULE);

	//Movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.7f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// CameraBoom
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetCapsuleComponent());
	CameraBoom->TargetArmLength = 900.f;
	CameraBoom->SetRelativeRotation(FRotator(-25.f, 0.f, 0.f));
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->bEnableCameraLag = true;

	// Camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	//Mesh
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));

	IsAttacking = false;
	SaveAttacking = false;

	PlayerInfo = new message::PosInfo();
	DestInfo = new message::PosInfo();

	CreatureStat->SetOwner(true, FName("PlayerCharacter"));
}

AJK1PlayerCharacter::~AJK1PlayerCharacter()
{
	delete PlayerInfo;
	delete DestInfo;
	PlayerInfo = nullptr;
	DestInfo = nullptr;
}

void AJK1PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<AJK1PlayerController>(UGameplayStatics::GetPlayerController(this, 0));
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

	DemoRaidState = Cast<AJK1DemoRaidState>(GetWorld()->GetGameState());
}

void AJK1PlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	{
		FVector Location = GetActorLocation();
		FRotator ActorRotation = GetActorRotation();
		PlayerInfo->set_x(Location.X);
		PlayerInfo->set_y(Location.Y);
		PlayerInfo->set_z(Location.Z);
		PlayerInfo->set_yaw(ActorRotation.Yaw);
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
				//info->set_yaw(DesiredYaw);
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

			// 현재 좌표와 서버로부터 받아오는 좌표를 받아와서, 방향 벡터 계산
			FVector CurrentLocation = GetActorLocation();
			FVector TargetLocation(DestInfo->x(), DestInfo->y(), DestInfo->z());
			FVector DirectionVector = TargetLocation - CurrentLocation;

			// 정규화
			DirectionVector.Normalize();

			AddMovementInput(DirectionVector);

			//FVector vec(DestInfo->x(), DestInfo->y(), DestInfo->z());
			//SetActorLocation(vec);

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

void AJK1PlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AJK1PlayerCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator CameraRotation = FollowCamera->GetComponentRotation();

	const FRotator YawRotation(0, Rotation.Yaw, 0);
	const FRotator CameraYawRotation(0, CameraRotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(CameraYawRotation).GetUnitAxis(EAxis::X);
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
	else
	{
		AddMovementInput(ForwardDirection, MovementVector.X);
		AddMovementInput(RightDirection, MovementVector.Y);
	}

}

void AJK1PlayerCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddControllerYawInput(-LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);
}

void AJK1PlayerCharacter::Attack()
{
	if (IsAttacking)
	{
		SaveAttacking = true;
	}
	else
	{
		IsAttacking = true;
		DoCombo();
	}
}

void AJK1PlayerCharacter::ComboActionBegin()
{
	UE_LOG(LogTemp, Log, TEXT("Save Attack : %d, CurrentCombo: %d"), SaveAttacking, CurrentCombo);

	if (SaveAttacking && CurrentCombo)
	{
		SaveAttacking = false;
		DoCombo();
	}
}

void AJK1PlayerCharacter::DoCombo()
{
}

void AJK1PlayerCharacter::ComboActionEnd()
{
	ensure(CurrentCombo != 0);
	CurrentCombo = 0;
	SaveAttacking = false;
	IsAttacking = false;
}

void AJK1PlayerCharacter::OnBasicAttackHit(TArray<FHitResult> HitResults)
{
}

void AJK1PlayerCharacter::SkillQ(const FInputActionValue& Value)
{
	UE_LOG(LogPlayerCharacter, Log, TEXT("This is Parent Class SKillQ"));
}

void AJK1PlayerCharacter::SkillE(const FInputActionValue& Value)
{
	UE_LOG(LogPlayerCharacter, Log, TEXT("This is Parent Class SKillE"));
}

void AJK1PlayerCharacter::SkillR(const FInputActionValue& Value)
{
	UE_LOG(LogPlayerCharacter, Log, TEXT("This is Parent Class SKillR"));
}

void AJK1PlayerCharacter::SkillLShift(const FInputActionValue& Value)
{
	UE_LOG(LogPlayerCharacter, Log, TEXT("This is Parent Class SKillLShift"));
}

void AJK1PlayerCharacter::SetMoveState(message::MoveState State)
{
	// 기존 상태와 같다면 스킵합니다.
	if (PlayerInfo->state() == State)
		return;

	PlayerInfo->set_state(State);
}

void AJK1PlayerCharacter::SetPlayerInfo(const message::PosInfo& Info)
{
	if (PlayerInfo->object_id() != 0)
		return;
	PlayerInfo->CopyFrom(Info);

	// 위치 동기화
	FVector Location(Info.x(), Info.y(), Info.z());
	SetActorLocation(Location);
}

void AJK1PlayerCharacter::SetDestInfo(const message::PosInfo& Info)
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

void AJK1PlayerCharacter::Death()
{
	Super::Death();

	Cast<AJK1PlayerController>(GetController())->RemoveInputSystem();
	UE_LOG(LogPlayerCharacter, Log, TEXT("Player is Down!!"));

	//if(DemoRaidState->GetDeathCount() > 0)
	//	Cast<AJK1PlayerController>(GetController())->ShowResurrection(true);
}

void AJK1PlayerCharacter::Resurrection()
{
	Cast<AJK1PlayerController>(GetController())->AttachInputSystem();
	Cast<AJK1PlayerController>(GetController())->ShowResurrection(false);
	
	DemoRaidState->UseDeathCount();
	CreatureStat->StatRecovery();
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	OnResurrection.Broadcast();
}

void AJK1PlayerCharacter::StartQTimer()
{
}

void AJK1PlayerCharacter::StartETimer()
{
}

void AJK1PlayerCharacter::StartRTimer()
{
}

void AJK1PlayerCharacter::StartLSTimer()
{
}

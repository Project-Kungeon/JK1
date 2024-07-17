// Copyright 2024 All Rights Reserved by J&K


#include "JK1PlayerCharacter.h"
#include "JK1/Physics/JK1Collision.h"
#include "JK1/Controller/Player/JK1PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "Animation/AnimMontage.h"

AJK1PlayerCharacter::AJK1PlayerCharacter()
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
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.7f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// CameraBoom
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 750.f;
	CameraBoom->SetRelativeRotation(FRotator(-20.f, 0.f, 0.f));
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
}

void AJK1PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<AJK1PlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	//if (PlayerController)
		//PlayerController->GetPlayerWidget()->SetWidgetsStat(CharacterStat, nullptr);
}

void AJK1PlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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



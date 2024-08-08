// Copyright 2024 All Rights Reserved by J&K


#include "JK1PlayerController.h"
#include "JK1LogChannels.h"
#include "Creature/PC/JK1PlayerCharacter.h"
#include "Creature/Monster/JK1MonsterBase.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Widget/JK1PlayerHUD.h"


AJK1PlayerController::AJK1PlayerController()
{
	//InputMappingContext & InputAction
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> InputMappingContextRef(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Input/IMC_JK1.IMC_JK1'"));
	if (nullptr != InputMappingContextRef.Object)
		DefaultMappingContext = InputMappingContextRef.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionMoveRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Action/IA_Move.IA_Move'"));
	if (nullptr != InputActionMoveRef.Object)
		MoveAction = InputActionMoveRef.Object;
	
	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionJumpRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Action/IA_Jump.IA_Jump'"));
	if (nullptr != InputActionJumpRef.Object)
		JumpAction = InputActionJumpRef.Object;
	
	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionLookRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Action/IA_Look.IA_Look'"));
	if (nullptr != InputActionLookRef.Object)
		LookAction = InputActionLookRef.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionLockOnRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Action/IA_LockOn.IA_LockOn'"));
	if (nullptr != InputActionLockOnRef.Object)
		LockOnAction = InputActionLockOnRef.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionAttackRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Action/IA_Attack.IA_Attack'"));
	if (nullptr != InputActionAttackRef.Object)
		AttackAction = InputActionAttackRef.Object;
	
	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionSkillRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Action/IA_Skill.IA_Skill'"));
	if (nullptr != InputActionSkillRef.Object)
		SkillAction = InputActionSkillRef.Object;


	//Widget
	static ConstructorHelpers::FClassFinder<UJK1PlayerHUD> Player_UI(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/Widget/Battle/WBP_OverlayWidget.WBP_OverlayWidget_C'"));
	if (Player_UI.Class)
	{
		HUDWidgetClass = Player_UI.Class;
	}

	LockOnDistance = 750.f;
}

void AJK1PlayerController::BeginPlay()
{
	//Cursor off When Play
	Super::BeginPlay();

	ControlledCharacter = GetCharacter();
	check(ControlledCharacter != nullptr);

	//FInputModeGameOnly GameOnlyInputMode;
	//SetInputMode(GameOnlyInputMode);
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
		//Input Priority
	}

	PlayerWidget = CreateWidget<UJK1PlayerHUD>(this, HUDWidgetClass);
	PlayerWidget->AddToViewport();
	UpdateWidget();
}

void AJK1PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AJK1PlayerController::JumpAct);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AJK1PlayerController::StopJumpingAct);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AJK1PlayerController::MoveAct);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AJK1PlayerController::LookAct);
		EnhancedInputComponent->BindAction(LockOnAction, ETriggerEvent::Started, this, &AJK1PlayerController::ToggleLockOn);
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &AJK1PlayerController::AttackAct);
		EnhancedInputComponent->BindAction(SkillAction, ETriggerEvent::Triggered, this, &AJK1PlayerController::SkillAct);
	}
}

void AJK1PlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);


	if (bShouldRotate && TargetActor)
	{
		FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(ControlledCharacter->GetActorLocation(), TargetActor->GetActorLocation());
		SetControlRotation(Rotation);
	}
}

void AJK1PlayerController::JumpAct()
{
	if(AJK1PlayerCharacter* ControlledPlayer = Cast<AJK1PlayerCharacter>(ControlledCharacter))
		ControlledPlayer->Jump();
}

void AJK1PlayerController::StopJumpingAct()
{
	if (AJK1PlayerCharacter* ControlledPlayer = Cast<AJK1PlayerCharacter>(ControlledCharacter))
		ControlledPlayer->StopJumping();
}

void AJK1PlayerController::LookAct(const FInputActionValue& Value)
{
	if (AJK1PlayerCharacter* ControlledPlayer = Cast<AJK1PlayerCharacter>(ControlledCharacter))
		ControlledPlayer->Look(Value);
}

void AJK1PlayerController::MoveAct(const FInputActionValue& Value)
{
	if (AJK1PlayerCharacter* ControlledPlayer = Cast<AJK1PlayerCharacter>(ControlledCharacter))
	{
		ControlledPlayer->Move(Value);
		UE_LOG(LogPlayerCharacter, Log, TEXT("%s"), *Value.ToString());
	}
}

void AJK1PlayerController::AttackAct()
{
	if (AJK1PlayerCharacter* ControlledPlayer = Cast<AJK1PlayerCharacter>(ControlledCharacter))
		ControlledPlayer->Attack();
}

void AJK1PlayerController::SkillAct(const FInputActionValue& Value)
{
	if (AJK1PlayerCharacter* ControlledPlayer = Cast<AJK1PlayerCharacter>(ControlledCharacter))
	{
		int index = static_cast<int>(Value.Get<float>());

		switch (index)
		{
		case 1:
			ControlledPlayer->SkillQ(Value);
			break;
		case 2:
			ControlledPlayer->SkillE(Value);
			break;
		case 3:
			ControlledPlayer->SkillR(Value);
			break;
		case 4:
			ControlledPlayer->SkillLShift(Value);
			break;
		}
	}
}

UJK1PlayerHUD* AJK1PlayerController::GetPlayerWidget() const
{
	return PlayerWidget;
}

void AJK1PlayerController::UpdateWidget()
{
	if (AJK1PlayerCharacter* ControlledPlayer = Cast<AJK1PlayerCharacter>(ControlledCharacter))
	{
		if (AJK1MonsterBase* TargetMonster = Cast<AJK1MonsterBase>(TargetActor))
			PlayerWidget->SetWidgetsStat(ControlledPlayer->CreatureStat, TargetMonster->CreatureStat);
		else
			PlayerWidget->SetWidgetsStat(ControlledPlayer->CreatureStat, nullptr);
	}
}

void AJK1PlayerController::ToggleLockOn()
{
	UE_LOG(LogPlayerController, Log, TEXT("Try Lock On"));
	if (bLockOnEngaged == false)
		EngagedLockOn();
	else
		DisengagedLockOn();
}

void AJK1PlayerController::EngagedLockOn()
{
	// 적 감지
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Emplace(UEngineTypes::ConvertToObjectType(ECC_Pawn));

	TArray<FHitResult> HitResults;

	// 감지 무시할 액터들 집어넣기
	TArray<AActor*> Ignore;
	Ignore.Add(ControlledCharacter);

	// TODO
	// 특정 클래스가 감지되지 않도록 or 특정 클래스만 감지하도록
	bool bSuccess = UKismetSystemLibrary::SphereTraceMultiForObjects(
		this,
		ControlledCharacter->GetActorLocation(),
		ControlledCharacter->GetActorLocation(),
		LockOnDistance,
		ObjectTypes,
		false,
		Ignore,
		EDrawDebugTrace::ForDuration,
		OUT HitResults,
		true,
		FLinearColor::Red,
		FLinearColor::Green,
		1.f);

	LockOnTargets.Empty();

	// 1단계 후보군 집어넣기
	if (bSuccess)
	{
		for (FHitResult Result : HitResults)
		{
			AActor* HitActor = Result.GetActor();
			LockOnTargets.Emplace(HitActor);
		}
	}

	// 2단계 가장 가까운 타겟
	float ClosestDistance = FLT_MAX;

	for (AActor* LockOnTarget : LockOnTargets)
	{
		float Distance = FVector::Distance(ControlledCharacter->GetActorLocation(), LockOnTarget->GetActorLocation());
		if (Distance < ClosestDistance)
		{
			ClosestDistance = Distance;
			TargetActor = LockOnTarget;
		}
	}

	// 3단계 기타 설정
	if (TargetActor != nullptr)
	{
		bLockOnEngaged = true;
		bShouldRotate = true;
		SetIgnoreLookInput(true);
		ControlledCharacter->GetCharacterMovement()->bOrientRotationToMovement = false;
		ControlledCharacter->GetCharacterMovement()->bUseControllerDesiredRotation = true;
		
		UE_LOG(LogPlayerController, Log, TEXT("Lock On to %s"), *(TargetActor->GetName()));
	}

	// Monster Info 위젯 설정
	UpdateWidget();
}

void AJK1PlayerController::DisengagedLockOn()
{
	LockOnTargets.Empty();

	bLockOnEngaged = false;
	bShouldRotate = false;
	ResetIgnoreLookInput();
	ControlledCharacter->GetCharacterMovement()->bOrientRotationToMovement = true;
	ControlledCharacter->GetCharacterMovement()->bUseControllerDesiredRotation = false;

	TargetActor = nullptr;
	
	UE_LOG(LogPlayerController, Log, TEXT("Lock Off"));

	// Monster Info 위젯 설정
	UpdateWidget();
}


// Copyright 2024 All Rights Reserved by J&K


#include "JK1PlayerController.h"
#include "JK1LogChannels.h"
#include "Creature/PC/JK1PlayerCharacter.h"
#include "Creature/Monster/JK1MonsterBase.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "InputMappingContext.h"
#include "InterActiveObject/NoticeBoard.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Widget/JK1PlayerHUD.h"
#include "Widget/JK1UserWidget.h"
#include "Widget/Lobby/JK1MatchingWidget.h"
#include "Blueprint/UserWidget.h"
#include "Interface/InteractiveObjectInterface.h"
#include "Creature/PC/JK1PlayerCharacter.h"
#include "Creature/JK1CreatureStatComponent.h"
#include "Item/JK1ItemInstance.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"


AJK1PlayerController::AJK1PlayerController()
{
	SetShowMouseCursor(false);

	//InputMappingContext
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> BattleInputMappingContextRef(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Input/IMC_JK1.IMC_JK1'"));
	if (nullptr != BattleInputMappingContextRef.Object)
		BattleMappingContext = BattleInputMappingContextRef.Object;
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> UIInputMappingContextRef(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Input/IMC_UI.IMC_UI'"));
	if (nullptr != UIInputMappingContextRef.Object)
		UIMappingContext = UIInputMappingContextRef.Object;
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> AttackInputMappingContextRef(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Input/IMC_Attack.IMC_Attack'"));
	if (nullptr != AttackInputMappingContextRef.Object)
		AttackMappingContext = AttackInputMappingContextRef.Object;

	// InputAction
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

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionUIRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Action/IA_UI.IA_UI'"));
	if (nullptr != InputActionUIRef.Object)
		UIInputAction = InputActionUIRef.Object;
	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionInterActRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Action/IA_InterAct.IA_InterAct'"));
	if (nullptr != InputActionInterActRef.Object)
		InterAction = InputActionInterActRef.Object;



	//Widget
	static ConstructorHelpers::FClassFinder<UJK1PlayerHUD> Player_UI(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/Widget/Battle/WBP_OverlayWidget.WBP_OverlayWidget_C'"));
	if (Player_UI.Class)
	{
		HUDWidgetClass = Player_UI.Class;
	}
	static ConstructorHelpers::FClassFinder<UUserWidget> Menu_UI(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/Widget/Basic/WBP_Menu.WBP_Menu_C'"));
	if (Menu_UI.Class)
	{
		MenuWidgetClass = Menu_UI.Class;
	}
	static ConstructorHelpers::FClassFinder<UUserWidget> Resurrection_UI(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/Widget/Battle/WBP_Resurrection.WBP_Resurrection_C'"));
	if (Resurrection_UI.Class)
	{
		ResurrectionWidgetClass = Resurrection_UI.Class;
	}
	static ConstructorHelpers::FClassFinder<UUserWidget> Inventory_UI(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/Widget/Item/Scene/WBP_SceneWidget.WBP_SceneWidget_C'"));
	if (Inventory_UI.Class)
	{
		InventoryWidgetClass = Inventory_UI.Class;
	}
	static ConstructorHelpers::FClassFinder<UUserWidget> Matching_UI(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/Widget/Lobby/WBP_MatchingWidget.WBP_MatchingWidget_C'"));
	if (Matching_UI.Class)
	{
		MatchingWidgetClass = Matching_UI.Class;
	}

	InterActDistance = 500.f;
	LockOnDistance = 750.f;
}

void AJK1PlayerController::BeginPlay()
{
	//Cursor off When Play
	Super::BeginPlay();

	ControlledCharacter = GetCharacter();
	check(ControlledCharacter != nullptr);
	SetInputMode(GameInputMode);
	
	Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(UIMappingContext, 0);
		Subsystem->AddMappingContext(BattleMappingContext, 1);
		//Input Priority
	}

	MenuWidget = CreateWidget<UUserWidget>(this, MenuWidgetClass);
	ResurrectionWidget = CreateWidget<UUserWidget>(this, ResurrectionWidgetClass);
	InventoryWidget = CreateWidget<UUserWidget>(this, InventoryWidgetClass);
	MatchingWidget = CreateWidget<UJK1MatchingWidget>(this, MatchingWidgetClass);
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
		EnhancedInputComponent->BindAction(UIInputAction, ETriggerEvent::Triggered, this, &AJK1PlayerController::ShowUI);
		EnhancedInputComponent->BindAction(InterAction, ETriggerEvent::Triggered, this, &AJK1PlayerController::InteractToObject);
	}
}

void AJK1PlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);


	if (bShouldRotate && TargetActor)
	{
		FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(GetCharacter()->GetActorLocation(), TargetActor->GetActorLocation());
		SetControlRotation(Rotation);
	}
}

void AJK1PlayerController::JumpAct()
{
	if (AJK1PlayerCharacter* ControlledPlayer = Cast<AJK1PlayerCharacter>(GetCharacter()))
	{
		ControlledPlayer->ChangeStatusEffect(true, 0);
		ControlledPlayer->Jump();
	}
}

void AJK1PlayerController::StopJumpingAct()
{
	if (AJK1PlayerCharacter* ControlledPlayer = Cast<AJK1PlayerCharacter>(GetCharacter()))
		ControlledPlayer->StopJumping();
}

void AJK1PlayerController::LookAct(const FInputActionValue& Value)
{
	if (AJK1PlayerCharacter* ControlledPlayer = Cast<AJK1PlayerCharacter>(GetCharacter()))
		ControlledPlayer->Look(Value);
}

void AJK1PlayerController::MoveAct(const FInputActionValue& Value)
{
	if (AJK1PlayerCharacter* ControlledPlayer = Cast<AJK1PlayerCharacter>(GetCharacter()))
	{
		ControlledPlayer->Move(Value);
		UE_LOG(LogPlayerCharacter, Log, TEXT("%s"), *Value.ToString());
	}
}

void AJK1PlayerController::StopAct(const FInputActionValue& Value)
{
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->RemoveActionBinding(2);
	}
}

void AJK1PlayerController::AttackAct()
{
	if (AJK1PlayerCharacter* ControlledPlayer = Cast<AJK1PlayerCharacter>(ControlledCharacter))
	{
		Subsystem->RemoveMappingContext(BattleMappingContext);

		ControlledPlayer->Attack();

		UAnimInstance* anim = ControlledPlayer->GetMesh()->GetAnimInstance();

		GetWorldTimerManager().SetTimer(UnMoveHandler, [this] {
			Subsystem->AddMappingContext(BattleMappingContext, 1);
			},
			0.43f, false);

		//(anim->GetCurrentActiveMontage()->GetPlayLength())-1.2f
		
	}
		
}

void AJK1PlayerController::SkillAct(const FInputActionValue& Value)
{
	if (AJK1PlayerCharacter* ControlledPlayer = Cast<AJK1PlayerCharacter>(GetCharacter()))
	{
		int index = static_cast<int>(Value.Get<float>());

		Subsystem->RemoveMappingContext(BattleMappingContext);

		switch (index)
		{
		case 1:
			ControlledPlayer->SkillQ(Value);
			GetWorldTimerManager().SetTimer(UnMoveHandler, [this] {
				Subsystem->AddMappingContext(BattleMappingContext, 1);
				},
				0.5f, false);
			break;
		case 2:
			ControlledPlayer->SkillE(Value);
			GetWorldTimerManager().SetTimer(UnMoveHandler, [this] {
				Subsystem->AddMappingContext(BattleMappingContext, 1);
				},
				0.5f, false);
			break;
		case 3:
			ControlledPlayer->SkillR(Value);
			GetWorldTimerManager().SetTimer(UnMoveHandler, [this] {
				Subsystem->AddMappingContext(BattleMappingContext, 1);
				},
				0.4f, false);
			break;
		case 4:
			ControlledPlayer->SkillLShift(Value);
			GetWorldTimerManager().SetTimer(UnMoveHandler, [this] {
				Subsystem->AddMappingContext(BattleMappingContext, 1);
				},
				0.55f, false);
			break;
		}
	}
}

void AJK1PlayerController::ShowUI(const FInputActionValue& Value)
{
	SetShowMouseCursor(true);
	if (AJK1PlayerCharacter* ControlledPlayer = Cast<AJK1PlayerCharacter>(ControlledCharacter))
	{
		SetInputMode(UIInputMode);
		SetShowMouseCursor(true);
		int index = static_cast<int>(Value.Get<float>());

		switch (index)
		{
		case 1:
			if (!OpenedWidget.IsEmpty())
				OpenedWidget.Pop()->RemoveFromParent();
			else
			{

				MenuWidget->AddToViewport();
				OpenedWidget.AddUnique(MenuWidget);
			}
			UE_LOG(LogPlayerController, Log, TEXT("input ESC"));
			break;
		case 2:
			// 인벤토리 갱신
			game::item::C_Item_OpenInventory pkt;
			pkt.set_player_id(Cast<AJK1PlayerCharacter>(GetCharacter())->CreatureStat->GetCreatureInfo()->object_info().object_id());
			SEND_PACKET(message::HEADER::ITEM_OPENINVENTORY, pkt);

			InventoryWidget->AddToViewport();
			OpenedWidget.AddUnique(InventoryWidget);
			UE_LOG(LogPlayerController, Log, TEXT("input Inventory"));
			break;
		case 3:
			// test matching success
			ResultMatching(true);
			break;
		case 4:
			// test matching fail
			ResultMatching(false);
			break;
		}
		

		if (OpenedWidget.IsEmpty())
		{
			SetInputMode(GameInputMode);
			SetShowMouseCursor(false);
		}
			
	}
}

void AJK1PlayerController::InteractToObject()
{
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Emplace(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));

	TArray<FHitResult> HitResults;

	// 감지 무시할 액터들 집어넣기
	TArray<AActor*> Ignore;
	if (ControlledCharacter == NULL)
	{
		ControlledCharacter = GetCharacter();
	}
	Ignore.Add(ControlledCharacter);

	bool bSuccess = UKismetSystemLibrary::SphereTraceMultiForObjects(
		this,
		ControlledCharacter->GetActorLocation(),
		ControlledCharacter->GetActorLocation(),
		InterActDistance,
		ObjectTypes,
		false,
		Ignore,
		EDrawDebugTrace::ForDuration,
		OUT HitResults,
		true,
		FLinearColor::Red,
		FLinearColor::Green,
		1.f);

	// 1단계 후보군 집어넣기
	if (bSuccess)
	{
		for (FHitResult Result : HitResults)
		{
			if (Cast<IInteractiveObjectInterface>(Result.GetActor()))
			{
				auto temp = Cast<AJK1ItemInstance>(Result.GetActor());	
				if (temp->CanInterAct())
				{
					temp->SetInterAct(false);
					temp->InterActive();
					//temp->Destroy();
				}
				else if (auto board = Cast<ANoticeBoard>(Result.GetActor()))
				{
					MatchingWidget->AddToViewport();
					OpenedWidget.AddUnique(MatchingWidget);
					SetShowMouseCursor(true);
					SetInputMode(UIInputMode);
				}

			}
			
		}
	}
}

void AJK1PlayerController::ShowResurrection(bool ononff)
{
	if (ononff)
	{
		SetInputMode(UIInputMode);
		SetShowMouseCursor(true);
		ResurrectionWidget->AddToViewport();
	}
	else
	{
		SetInputMode(GameInputMode);
		SetShowMouseCursor(false);
		ResurrectionWidget->RemoveFromParent();
	}
}

UJK1PlayerHUD* AJK1PlayerController::GetPlayerWidget() const
{
	return PlayerWidget;
}

void AJK1PlayerController::UpdateWidget()
{
	if (AJK1PlayerCharacter* ControlledPlayer = Cast<AJK1PlayerCharacter>(GetCharacter()))
	{
		if (AJK1MonsterBase* TargetMonster = Cast<AJK1MonsterBase>(TargetActor))
			PlayerWidget->SetWidgetsStat(ControlledPlayer->CreatureStat, TargetMonster->CreatureStat);
		else
			PlayerWidget->SetWidgetsStat(ControlledPlayer->CreatureStat, nullptr);
	}
}

void AJK1PlayerController::UpdateControlledCharacter()
{
	ControlledCharacter = GetCharacter();
}

void AJK1PlayerController::AttachInputSystem()
{
	Subsystem->AddMappingContext(BattleMappingContext, 1);
}

void AJK1PlayerController::RemoveInputSystem()
{
	Subsystem->RemoveMappingContext(BattleMappingContext);
}

void AJK1PlayerController::ToggleLockOn()
{
	UE_LOG(LogPlayerController, Log, TEXT("Try Lock On"));
	// delegate test
	UpdateMatching(true);
	UpdateMatching(false);

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
	Ignore.Add(GetCharacter());

	// TODO
	// 특정 클래스가 감지되지 않도록 or 특정 클래스만 감지하도록
	bool bSuccess = UKismetSystemLibrary::SphereTraceMultiForObjects(
		this,
		GetCharacter()->GetActorLocation(),
		GetCharacter()->GetActorLocation(),
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
		float Distance = FVector::Distance(GetCharacter()->GetActorLocation(), LockOnTarget->GetActorLocation());
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
		GetCharacter()->GetCharacterMovement()->bOrientRotationToMovement = false;
		GetCharacter()->GetCharacterMovement()->bUseControllerDesiredRotation = true;
		
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
	GetCharacter()->GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacter()->GetCharacterMovement()->bUseControllerDesiredRotation = false;

	TargetActor = nullptr;
	
	UE_LOG(LogPlayerController, Log, TEXT("Lock Off"));

	// Monster Info 위젯 설정
	UpdateWidget();
}

void AJK1PlayerController::UpdateMatching(bool IsAccept)
{
	// 다른 클라이언트들의 매칭 수락 여부 패킷이 온 경우
	MatchingWidget->OnMatchingUpdate.Execute(IsAccept);


}

void AJK1PlayerController::ResultMatching(bool IsSuccess)
{
	// 성공 했으면 ui 제거 및 맵 이동
	if (IsSuccess)
	{
		MatchingWidget->RemoveFromParent();
		UGameplayStatics::OpenLevel(this, FName(TEXT("L_DemoRaid")));

	}
	else   // 실패 하면 accept ui만 제거
		MatchingWidget->MatchingFail();
}


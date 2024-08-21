// Copyright 2024 All Rights Reserved by J&K


#include "JK1PlayerController.h"
#include "../../Creature/PC/JK1PlayerCharacter.h"
#include "GameFramework/Character.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

AJK1PlayerController::AJK1PlayerController()
{
	//InputMappingContext & InputAction
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> InputMappingContextRef(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Input/IMC_JK1.IMC_JK1'"));
	if (nullptr != InputMappingContextRef.Object)
	{
		DefaultMappingContext = InputMappingContextRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionMoveRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Action/IA_Move.IA_Move'"));
	if (nullptr != InputActionMoveRef.Object)
	{
		MoveAction = InputActionMoveRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionJumpRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Action/IA_Jump.IA_Jump'"));
	if (nullptr != InputActionJumpRef.Object)
	{
		JumpAction = InputActionJumpRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionLookRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Action/IA_Look.IA_Look'"));
	if (nullptr != InputActionLookRef.Object)
	{
		LookAction = InputActionLookRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionAttackRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Action/IA_Attack.IA_Attack'"));
	if (nullptr != InputActionAttackRef.Object)
	{
		AttackAction = InputActionAttackRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionSkillRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/Action/IA_Skill.IA_Skill'"));
	if (nullptr != InputActionSkillRef.Object)
	{
		SkillAction = InputActionSkillRef.Object;
	}
}

void AJK1PlayerController::BeginPlay()
{
	//Cursor off When Play
	Super::BeginPlay();

	FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode);
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
		//Input Priority
	}
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
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &AJK1PlayerController::AttackAct);
		EnhancedInputComponent->BindAction(SkillAction, ETriggerEvent::Triggered, this, &AJK1PlayerController::SkillAct);
	}
}

void AJK1PlayerController::JumpAct()
{
	AJK1PlayerCharacter* ControlledCharacter = Cast<AJK1PlayerCharacter>(GetPawn());
	if (ControlledCharacter)
	{
		ControlledCharacter->Jump();
	}
}

void AJK1PlayerController::StopJumpingAct()
{
	AJK1PlayerCharacter* ControlledCharacter = Cast<AJK1PlayerCharacter>(GetPawn());
	if (ControlledCharacter)
	{
		ControlledCharacter->StopJumping();
	}
}

void AJK1PlayerController::LookAct(const FInputActionValue& Value)
{
	AJK1PlayerCharacter* ControlledCharacter = Cast<AJK1PlayerCharacter>(GetPawn());
	if (ControlledCharacter)
	{
		ControlledCharacter->Look(Value);
	}
}

void AJK1PlayerController::MoveAct(const FInputActionValue& Value)
{

	AJK1PlayerCharacter* ControlledCharacter = Cast<AJK1PlayerCharacter>(GetPawn());
	if (ControlledCharacter)
	{
		ControlledCharacter->Move(Value);
		UE_LOG(LogPlayerController, Log, TEXT("%s"), *Value.ToString());
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
	AJK1PlayerCharacter* ControlledCharacter = Cast<AJK1PlayerCharacter>(GetPawn());
	if (ControlledCharacter)
	{
		ControlledCharacter->Attack();
	}
}

void AJK1PlayerController::SkillAct(const FInputActionValue& Value)
{
	AJK1PlayerCharacter* ControlledCharacter = Cast<AJK1PlayerCharacter>(GetPawn());
	if (ControlledCharacter)
	{
		int index = static_cast<int>(Value.Get<float>());

		switch (index)
		{
		case 1:
			ControlledCharacter->SkillQ(Value);
			break;
		case 2:
			ControlledCharacter->SkillE(Value);
			break;
		case 3:
			ControlledCharacter->SkillR(Value);
			break;
		case 4:
			ControlledCharacter->SkillLShift(Value);
			break;
		}		
	}
}


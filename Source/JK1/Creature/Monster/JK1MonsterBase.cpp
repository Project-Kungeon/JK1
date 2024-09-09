// Copyright 2024 All Rights Reserved by J&K


#include "JK1MonsterBase.h"
#include "../JK1CreatureStatComponent.h"
#include "Components/WidgetComponent.h"
#include "Creature/PC/JK1PlayerCharacter.h"
#include "Widget/JK1UserWidget.h"
#include "AIController.h"
#include <BrainComponent.h>


AJK1MonsterBase::AJK1MonsterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	CreatureStat->SetOwner(false, FName("MonsterBase"));

	MonsterWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("MonsterWidget"));
	MonsterWidget->SetupAttachment(GetRootComponent());
	MonsterWidget->SetRelativeLocation(FVector(0.f, 0.f, 100.f));
	MonsterWidget->SetWidgetSpace(EWidgetSpace::Screen);

	static ConstructorHelpers::FClassFinder<UUserWidget> Monster_UI(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/Widget/Battle/WBP_HealthBar.WBP_HealthBar_C'"));
	if (Monster_UI.Succeeded())
	{
		MonsterWidget->SetWidgetClass(Monster_UI.Class);
		MonsterWidget->SetDrawSize(FVector2D(50.f, 10.f));
	}

	//AIControllerClass = AJK1MonsterBaseController::StaticClass();
	//AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	DoGimmic = false;
}

void AJK1MonsterBase::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogMonster, Log, TEXT("MonsterBase: Beginplay Call"));
	
	MonsterWidget->InitWidget();
	auto CreatureWidget = Cast<UJK1UserWidget>(MonsterWidget->GetUserWidgetObject());
	if (CreatureWidget != nullptr)
	{
		CreatureWidget->BindCreatureStat(CreatureStat);
	}
	else
		UE_LOG(LogMonster, Error, TEXT("Failed to Cast to UHealthBarWidget"));
}

void AJK1MonsterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AJK1MonsterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AJK1MonsterBase::HighlightActor()
{
	bHighlighted = true;
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(250);
}

void AJK1MonsterBase::UnHighlightActor()
{
	bHighlighted = false;
	GetMesh()->SetRenderCustomDepth(false);
}

void AJK1MonsterBase::Death()
{
	Super::Death();
	Cast<AAIController>(GetController())->GetBrainComponent()->StopLogic(TEXT("DEAD"));

	FTimerHandle TimerHandle;
	FTimerDelegate TimerCallback;
	TimerCallback.BindLambda(
		[this, &TimerHandle]
		{
			this->Destroy();
			GetWorldTimerManager().ClearTimer(TimerHandle);
		});
	GetWorldTimerManager().SetTimer(TimerHandle, TimerCallback, 5.f, false);
}

void AJK1MonsterBase::GiveStatusEffect(int type)
{
	// 포효 처리 도중에 detect가 실행돼서 비워지면?

	// 대안으로 생각해본 것
	// detect 로직은 램페이지 구현
	// BT_detect에선 tick마다 램페이지 detect 실행(gimmic중이 아닐때만)
	// gimmic중이라면 detect x, 해당 gimmic 로직 내부에서 detect 실행

	//  => 모든 client들의 램페이지가 detect를 실행해 자체적인 target을 가질 것
	// 모든 player의 위치가 동기화 되었기에 거의 같은 대상을 감지하겠지만 
	// network 속도 차이에 의해 어떤 client는 detect가 실행되기 전에 대상이 범위 밖으로 나가 결과가 달라질 수 있음
	if (!DetectTargets.IsEmpty())
	{
		for (AJK1PlayerCharacter* target : DetectTargets)
		{
			if (target)
				target->ChangeStatusEffect(true, type);	
		}
	}
}
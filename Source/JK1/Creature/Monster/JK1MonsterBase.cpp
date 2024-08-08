// Copyright 2024 All Rights Reserved by J&K


#include "JK1MonsterBase.h"
#include "../JK1CreatureStatComponent.h"
//#include "Creature/Monster/AI/MonsterBaseController.h"
#include "Components/WidgetComponent.h"
#include "Widget/JK1UserWidget.h"


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

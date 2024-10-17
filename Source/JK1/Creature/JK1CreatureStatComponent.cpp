// Copyright 2024 All Rights Reserved by J&K


#include "JK1CreatureStatComponent.h"
#include "JK1CreatureBase.h"
#include "../JK1GameInstance.h"
#include "../Controller/Player/JK1PlayerController.h"

#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UJK1CreatureStatComponent::UJK1CreatureStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;

	CreatureInfo = new message::CreatureInfo();
}


// Called when the game starts
void UJK1CreatureStatComponent::BeginPlay()
{
	Super::BeginPlay();

	LoadData();
}

void UJK1CreatureStatComponent::InitializeComponent()
{
	IsImmunity = false;

	// initialize stat
	BasicStatData = nullptr;
	CurrentHP = 0;
	CurrentExp = 0;
	CurrentLevel = 1;
	CurrentStat[0] = 0;
	CurrentStat[1] = 0;
}

// Called every frame
void UJK1CreatureStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UJK1CreatureStatComponent::LoadData()
{
	UJK1GameInstance* JK1GameInstance = Cast<UJK1GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	check(JK1GameInstance != nullptr);

	if (IsPlayer)
		BasicStatData = JK1GameInstance->GetJK1PlayerData(Name);
	else
		BasicStatData = JK1GameInstance->GetJK1MonsterData(Name);

	if (BasicStatData != nullptr)
	{
		StatRecovery();
		UE_LOG(LogSystem, Log, TEXT("Set (%s)'s Default Stat"), *Name.ToString());
	}
	else
		UE_LOG(LogSystem, Error, TEXT("(%s) data doesn't exist"), *Name.ToString());
}

void UJK1CreatureStatComponent::SetCurrentHP(float NewHP)
{
	AsyncTask(ENamedThreads::GameThread, [this, NewHP]() {
		CurrentHP = NewHP;
		UE_LOG(LogSystem, Log, TEXT("Remain HP : %f"), CurrentHP);
		OnHPChanged.Broadcast();

		if (CurrentHP <= 0.f)
		{
			CurrentHP = 0.f;
			OnHPIsZero.Broadcast();

			//// TEMP CODE
			//if (!DamageInstigator.IsEmpty())
			//{
			//	TArray<AActor*> temp;
			//	DamageInstigator.GetKeys(temp);

			//	for (AActor* instigator : temp)
			//	{
			//		if(auto player = Cast<AJK1PlayerController>(instigator))
			//			if (auto Character = Cast<AJK1CreatureBase>(player->GetPawn()))
			//			{
			//				Character->CreatureStat->PlusExp(BasicStatData->Exp);
			//				Cast<AJK1PlayerController>(Character->GetController())->DisengagedLockOn();
			//			}
			//	}
			//}
		}
		});
	
}

void UJK1CreatureStatComponent::SetStat(int index, float value)
{
	CurrentStat[index] = value;

	// For Debugging
	FString statname;
	switch (index)
	{
	case 0:
		statname = "ATK";
		break;
	case 1:
		statname = "DEF";
		break;
	}

	UE_LOG(LogSystem, Log, TEXT("Current %s : %f"), *statname, CurrentStat[index]);
}

void UJK1CreatureStatComponent::PlusExp(float Exp)
{
	CurrentExp += Exp;
	OnExpChanged.Broadcast();

	// TODO
	// Exp 초과 시 레벨 올리고 broadcast
	if (CurrentExp >= BasicStatData->Exp)
	{
		CurrentExp -= BasicStatData->Exp;
		OnExpChanged.Broadcast();

		CurrentLevel += 1;
		LevelUP(CurrentLevel);
		OnLevelUp.Broadcast();
	}
}

void UJK1CreatureStatComponent::LevelUP(int level)
{
	// 레벨업을 했을 때 스탯 변화를 어캐할 것인가
	// 1. 레벨에 맞는 스탯표를 만들어 그에 맞게 변화
	// 2. 단순히 레벨업 당 단순 수치 추가
	// ex) hp+100, stat+1
	CurrentHP += 100;
	CurrentStat[0] += 10;
	CurrentStat[1] += 10;
}

void UJK1CreatureStatComponent::StatRecovery()
{
	SetCurrentHP(BasicStatData->MaxHP);
	SetStat(0, BasicStatData->ATK);
	SetStat(1, BasicStatData->DEF);
}

bool UJK1CreatureStatComponent::HitDamage(float NewDamage, AActor* instigator)
{
	if (IsImmunity)
		return false;

	if (IsParry)
	{
		OnDamaged.Broadcast();
		return false;
	}

	check(BasicStatData != nullptr);
	DamageInstigator.Add(instigator, NewDamage);

	SetCurrentHP(FMath::Clamp<float>( CurrentHP - NewDamage / CurrentStat[1], 0.f, BasicStatData->MaxHP));
	UE_LOG(LogSystem, Log, TEXT("Hit Damage: %f"), NewDamage);

	return true;
}

float UJK1CreatureStatComponent::TotalDamageBy(AActor* instigator)
{
	if (!DamageInstigator.Contains(instigator))
		return -1;
	
	float total = 0;
	for (auto it : DamageInstigator)
	{
		if (it.Key == instigator)
			total += it.Value;
	}

	return total;
}

FName UJK1CreatureStatComponent::GetCharacterName()
{
	return Name;
}

float UJK1CreatureStatComponent::GetCurrentHP()
{
	return CurrentHP;
}

float UJK1CreatureStatComponent::GetMaxHp()
{
	return BasicStatData->MaxHP;
}

int32 UJK1CreatureStatComponent::GetCurrentLevel()
{
	return CurrentLevel;
}

float UJK1CreatureStatComponent::GetHPRatio()
{
	check(BasicStatData != nullptr);
	return (BasicStatData->MaxHP < KINDA_SMALL_NUMBER) ? 0.f : (CurrentHP / BasicStatData->MaxHP);
}

void UJK1CreatureStatComponent::SetCreatureInfo(message::CreatureInfo Info)
{
	if (CreatureInfo->object_info().object_id() != 0)
		return;
	CreatureInfo->CopyFrom(Info);
}

float UJK1CreatureStatComponent::GetExpRatio()
{
	check(BasicStatData != nullptr);
	return (BasicStatData->Exp < KINDA_SMALL_NUMBER) ? 0.f : (CurrentExp / BasicStatData->Exp);
}
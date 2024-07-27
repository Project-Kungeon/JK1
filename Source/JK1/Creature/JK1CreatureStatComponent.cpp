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

	ObjectInfo = new message::ObjectInfo();
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
	// initialize stat
	BasicStatData = nullptr;
	IsPlayer = true;
	CurrentHP = 0;
	CurrentExp = 0;
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
		SetHP(BasicStatData->MaxHP);
		SetStat(0, BasicStatData->ATK);
		SetStat(1, BasicStatData->DEF);
		UE_LOG(LogSystem, Log, TEXT("Set (%s)'s Default Stat"), *Name.ToString());
	}
	else
		UE_LOG(LogSystem, Error, TEXT("(%s) data doesn't exist"), *Name.ToString());
}

void UJK1CreatureStatComponent::SetHP(float NewHP)
{
	
	CurrentHP = NewHP;
	UE_LOG(LogSystem, Log, TEXT("Remain HP : %f"), CurrentHP);
	//OnHPChanged.Broadcast();

	if (CurrentHP <= KINDA_SMALL_NUMBER)
	{
		CurrentHP = 0.f;
		//OnHPIsZero.Broadcast();

		// TEMP CODE
		//if (!DamageInstigator.IsEmpty())
		//{
		//	for (AJ1PlayerController* instigator : DamageInstigator)
		//	{
		//		if (auto character = Cast<ACharacterBase>(instigator->GetPawn()))
		//		{
		//			character->CharacterStat->PlusExp(CurrentStatData->DropExp);
		//		}
		//	}
		//}
	}
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

	// TODO
	// Exp 초과 시 레벨 올리고 broadcast

}

void UJK1CreatureStatComponent::HitDamage(float NewDamage)
{
	check(BasicStatData != nullptr);
	
	// 서버와 의논
	//if (AJK1PlayerController* DamageActorController = Cast<AJK1PlayerController>(instigator))
		//DamageInstigator.AddUnique(DamageActorController);

	SetHP(FMath::Clamp<float>(CurrentHP - NewDamage/CurrentStat[1], 0.f, BasicStatData->MaxHP));
	UE_LOG(LogSystem, Log, TEXT("Hit Damage: %f"), NewDamage);
}

void UJK1CreatureStatComponent::SetObjectInfo(message::ObjectInfo Info)
{
	if (ObjectInfo->object_id() != 0)
		return;
	ObjectInfo->CopyFrom(Info);
}

void UJK1CreatureStatComponent::SetCreatureInfo(message::CreatureInfo Info)
{
	if (CreatureInfo->object_id() != 0)
		return;
	CreatureInfo->CopyFrom(Info);
}

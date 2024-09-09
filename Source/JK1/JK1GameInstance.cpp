// Copyright 2024 All Rights Reserved by J&K


#include "JK1GameInstance.h"
#include "JK1LogChannels.h"

UJK1GameInstance::UJK1GameInstance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_JK1Player(TEXT("/Script/Engine.DataTable'/Game/Data/DT_PlayerStatData.DT_PlayerStatData'"));
	check(DT_JK1Player.Succeeded());
	JK1PlayerTable = DT_JK1Player.Object;
	check(JK1PlayerTable->GetRowMap().Num() > 0);
	
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_JK1Monster(TEXT("/Script/Engine.DataTable'/Game/Data/DT_MonsterStatData.DT_MonsterStatData'"));
	check(DT_JK1Monster.Succeeded());
	JK1MonsterTable = DT_JK1Monster.Object;
	check(JK1MonsterTable->GetRowMap().Num() > 0);
}

void UJK1GameInstance::Init()
{
	Super::Init();

	UE_LOG(LogSystem, Log, TEXT("ExpForNextLevel 2 JK1Player : %f"), GetJK1PlayerData(FName(TEXT("Warrior")))->Exp);
	UE_LOG(LogSystem, Log, TEXT("DropExp 2 JK1Monster : %f"), GetJK1MonsterData(FName(TEXT("MonsterBase")))->Exp);
}

FJK1CreatureData* UJK1GameInstance::GetJK1PlayerData(FName ClassName)
{
	return JK1PlayerTable->FindRow<FJK1CreatureData>(ClassName, TEXT(""));
}

FJK1CreatureData* UJK1GameInstance::GetJK1MonsterData(FName MonsterName)
{
	return JK1MonsterTable->FindRow<FJK1CreatureData>(MonsterName, TEXT(""));
}

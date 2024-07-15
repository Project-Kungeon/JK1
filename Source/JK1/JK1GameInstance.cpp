// Copyright 2024 All Rights Reserved by J&K


#include "JK1GameInstance.h"

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

	UE_LOG(LogTemp, Warning, TEXT("ExpForNextLevel 2 J1Player : %d"), GetJK1PlayerData(FName(TEXT("Warrior")))->Exp);
	UE_LOG(LogTemp, Warning, TEXT("DropExp 2 J1Monster : %d"), GetJK1MonsterData(FName(TEXT("GoblinSpear")))->Exp);
}

FJK1CreatureData* UJK1GameInstance::GetJK1PlayerData(FName ClassName)
{
	return JK1PlayerTable->FindRow<FJK1CreatureData>(ClassName, TEXT(""));
}

FJK1CreatureData* UJK1GameInstance::GetJK1MonsterData(FName MonsterName)
{
	return JK1MonsterTable->FindRow<FJK1CreatureData>(MonsterName, TEXT(""));
}

#include "JK1PlayerHUD.h"


void UJK1PlayerHUD::NativeConstruct()
{
	Super::NativeConstruct();

	HealthBar = Cast<UJK1UserWidget>(GetWidgetFromName(TEXT("HealthBar")));
	check(HealthBar != nullptr);

	ExpBar = Cast<UJK1UserWidget>(GetWidgetFromName(TEXT("ExpBar")));
	check(ExpBar != nullptr);

	LockOnMonsterInfo = Cast<UJK1UserWidget>(GetWidgetFromName(TEXT("LockOnMonsterInfo")));
	check(LockOnMonsterInfo != nullptr);
}

void UJK1PlayerHUD::SetWidgetsStat(UJK1CreatureStatComponent* PlayerStat, UJK1CreatureStatComponent* MonsterStat)
{
	CurrentCreatureStat = PlayerStat;
	if (PlayerStat != nullptr)
	{
		HealthBar->BindCreatureStat(PlayerStat);
		ExpBar->BindCreatureStat(PlayerStat);
	}

	if (MonsterStat != nullptr)
	{
		LockOnMonsterInfo->BindCreatureStat(MonsterStat);
		LockOnMonsterInfo->SetVisibility(ESlateVisibility::Visible);
	}
	else
		LockOnMonsterInfo->SetVisibility(ESlateVisibility::Collapsed);

	UpdateInfo();
}
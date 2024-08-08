// Copyright 2024 All Rights Reserved by J&K

#pragma once

#include "CoreMinimal.h"
#include "JK1UserWidget.h"
#include "JK1PlayerHUD.generated.h"

class UJK1UserWidget;

/**
 *
 */
UCLASS()
class JK1_API UJK1PlayerHUD : public UJK1UserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	void SetWidgetsStat(UJK1CreatureStatComponent* PlayerStat, UJK1CreatureStatComponent* MonsterStat);

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateInfo();

private:
	TObjectPtr<UJK1UserWidget> HealthBar;

	TObjectPtr<UJK1UserWidget> ExpBar;

	TObjectPtr<UJK1UserWidget> LockOnMonsterInfo;

};
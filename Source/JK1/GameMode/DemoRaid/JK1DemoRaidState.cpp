// Copyright 2024 All Rights Reserved by J&K


#include "GameMode/DemoRaid/JK1DemoRaidState.h"

AJK1DemoRaidState::AJK1DemoRaidState()
{
	DeathCount = 1;
}
void AJK1DemoRaidState::UseDeathCount()
{
	if (DeathCount > 0)
	{
		DeathCount -= 1;

		//여기에 ui 갱신 함수 연결
		OnDeathCountChange.Broadcast();
	}
}

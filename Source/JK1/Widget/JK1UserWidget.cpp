#include "JK1UserWidget.h"
#include "Creature/JK1CreatureStatComponent.h"

void UJK1UserWidget::BindCreatureStat(UJK1CreatureStatComponent* StatComponent)
{
	check(StatComponent != nullptr);
	CurrentCreatureStat = StatComponent;
	SetCreatureStat();
}
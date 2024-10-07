// Copyright 2024 All Rights Reserved by J&K

#pragma once

#include "CoreMinimal.h"
#include "Creature/Monster/Boss/JK1Rampage.h"
#include "NJK1Rampage.generated.h"

/**
 * 
 */
UCLASS()
class JK1_API ANJK1Rampage : public AJK1Rampage
{
	GENERATED_BODY()
	
public:
	ANJK1Rampage();

public:
	virtual void CheckBATrace() override;
	virtual void CheckFistTrace() override;

	virtual void	OnBasicAttackHit(TArray<FHitResult> HitResults) override;

};

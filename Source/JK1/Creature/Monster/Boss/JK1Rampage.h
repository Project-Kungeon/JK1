// Copyright 2024 All Rights Reserved by J&K

#pragma once

#include "CoreMinimal.h"
#include "Creature/Monster/JK1MonsterBase.h"
#include "JK1Rampage.generated.h"

/**
 * 
 */
UCLASS()
class JK1_API AJK1Rampage : public AJK1MonsterBase
{
	GENERATED_BODY()

public:
	AJK1Rampage();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
};

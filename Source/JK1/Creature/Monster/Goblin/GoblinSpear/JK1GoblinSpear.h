// Copyright 2024 All Rights Reserved by J&K

#pragma once

#include "CoreMinimal.h"
#include "../JK1GoblinBase.h"
#include "JK1GoblinSpear.generated.h"

/**
 *
 */
UCLASS()
class JK1_API AJK1GoblinSpear : public AJK1GoblinBase
{
	GENERATED_BODY()

public:
	AJK1GoblinSpear();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};

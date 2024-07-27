// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "JK1.h"
#include "../JK1LogChannels.h"
#include "JK1CreatureBase.generated.h"

UCLASS()
class JK1_API AJK1CreatureBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AJK1CreatureBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCursor) override;
	virtual void PossessedBy(AController* NewController) override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stat)
	TObjectPtr<class UJK1CreatureStatComponent> CreatureStat;
};

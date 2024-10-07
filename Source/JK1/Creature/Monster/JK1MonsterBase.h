// Copyright 2024 All Rights Reserved by J&K

#pragma once

#include "CoreMinimal.h"
#include "../JK1CreatureBase.h"
#include "JK1/Interface/MonsterInterface.h"
#include "JK1MonsterBase.generated.h"

class AJK1PlayerCharacter;
/**
 * 
 */
UCLASS()
class JK1_API AJK1MonsterBase : public AJK1CreatureBase, public IMonsterInterface
{
	GENERATED_BODY()

public:
	AJK1MonsterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void	OnBasicAttackHit(TArray<FHitResult> HitResults) override;

	/*
	*  Member Function
	*/
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	virtual void Death() override;


	void GiveStatusEffect(int type);


	/*
	*  Member Variable
	*/
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<class UWidgetComponent> MonsterWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackDistance;

	UPROPERTY(BlueprintReadWrite)
	bool bHighlighted = false;
	
public:
	TArray<AJK1PlayerCharacter*> DetectTargets;
	bool DoGimmic;
};

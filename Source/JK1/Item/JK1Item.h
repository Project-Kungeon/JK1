// Copyright 2024 All Rights Reserved by J&K

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JK1Define.h"
#include "JK1/Interface/InteractiveObjectInterface.h"
#include "JK1Item.generated.h"

class AJK1PlayerCharacter;

UCLASS()
class JK1_API AJK1Item : public AActor, public IInteractiveObjectInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJK1Item();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	virtual void UseItem(AJK1PlayerCharacter* OwningPlayer);
	virtual void InterActive() override;

protected:
	UPROPERTY()
	int32 ItemID = 1;

	UPROPERTY()
	EItemRarity ItemRarity = EItemRarity::Junk;

	UPROPERTY()
	EItemType type = EItemType::Consumable;

};

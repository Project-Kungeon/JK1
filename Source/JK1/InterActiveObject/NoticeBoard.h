// Copyright 2024 All Rights Reserved by J&K

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JK1/Interface/InteractiveObjectInterface.h"
#include "NoticeBoard.generated.h"

UCLASS()
class JK1_API ANoticeBoard : public AActor, public IInteractiveObjectInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANoticeBoard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	virtual void	InterActive() override;
	UUserWidget*	ReturnWidget();

protected:
	

};

// Copyright 2024 All Rights Reserved by J&K

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MonsterInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMonsterInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class JK1_API IMonsterInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void HighlightActor() = 0;
	virtual void UnHighlightActor() = 0;
};

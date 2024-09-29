// Copyright 2024 All Rights Reserved by J&K

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractiveObjectInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractiveObjectInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class JK1_API IInteractiveObjectInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void InterActive() abstract;
	bool CanInterAct() { return InterAct; }
	void SetInterAct(bool OnOff) { InterAct = OnOff; }

private:
	bool InterAct = true;
};

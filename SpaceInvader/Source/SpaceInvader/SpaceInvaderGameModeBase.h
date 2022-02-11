// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SpaceInvaderGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SPACEINVADER_API ASpaceInvaderGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	void BeginPlay() override final;

};

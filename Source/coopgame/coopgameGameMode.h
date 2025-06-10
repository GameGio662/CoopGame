// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "coopgameGameMode.generated.h"

UCLASS(minimalapi)
class AcoopgameGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AcoopgameGameMode();

	virtual void PostLogin(APlayerController* NewPlayer) override;
};



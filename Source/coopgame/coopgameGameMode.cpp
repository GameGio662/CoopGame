// Copyright Epic Games, Inc. All Rights Reserved.

#include "coopgameGameMode.h"
#include "coopgameCharacter.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/PlayerStart.h"
#include "Engine/World.h"

AcoopgameGameMode::AcoopgameGameMode()
{
	DefaultPawnClass = AcoopgameCharacter::StaticClass();
}

void AcoopgameGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (NewPlayer && !NewPlayer->GetPawn())
	{
		TArray<AActor*> PlayerStarts;
		UGameplayStatics::GetAllActorsOfClass(this, APlayerStart::StaticClass(), PlayerStarts);

		if (PlayerStarts.Num() > 0)
		{
			AActor* ChosenStart = PlayerStarts[FMath::RandRange(0, PlayerStarts.Num() - 1)];

			FVector SpawnLocation = ChosenStart->GetActorLocation();
			FRotator SpawnRotation = ChosenStart->GetActorRotation();

			APawn* NewPawn = GetWorld()->SpawnActor<APawn>(DefaultPawnClass, SpawnLocation, SpawnRotation);
			if (NewPawn)
			{
				NewPlayer->Possess(NewPawn);
			}
		}
	}
}
// Copyright Epic Games, Inc. All Rights Reserved.


#include "SpaceInvaderGameModeBase.h"

void ASpaceInvaderGameModeBase::BeginPlay() {
	Super::BeginPlay();

	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
}

void ASpaceInvaderGameModeBase::Tick(float DeltaTime) {
}

void ASpaceInvaderGameModeBase::SpawnEnemies() {
	UWorld* World = GetWorld();

	if (World) {

	}
}

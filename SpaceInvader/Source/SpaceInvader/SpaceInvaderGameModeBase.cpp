// Copyright Epic Games, Inc. All Rights Reserved.


#include "SpaceInvaderGameModeBase.h"
#include "BaseEnemy.h"
#include "Kismet/KismetMathLibrary.h"

ASpaceInvaderGameModeBase::ASpaceInvaderGameModeBase() {
	PrimaryActorTick.bCanEverTick = true;
}

void ASpaceInvaderGameModeBase::BeginPlay() {
	Super::BeginPlay();

	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;

	for (int i = 0; i < NumEnemiesWaveOne; i++) {
		SpawnEnemies(0);
		CurrentEnemyCount++;
		//EnemyArray[i]->OnDestroyed.AddDynamic
	}
}

void ASpaceInvaderGameModeBase::Tick(float DeltaTime) {
	if (CurrentEnemyCount <= 0) {
		EnemyArray.Empty();
		CurrentWave++;
		switch (CurrentWave) {
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		default:
			break;
		}
	}
}

void ASpaceInvaderGameModeBase::SpawnEnemies(int32 EnemyType) {
	UWorld* World = GetWorld();
	float RandNum = FMath::FRandRange(0.f,UKismetMathLibrary::GetTAU());
	if (World) {
		ABaseEnemy* tempEnemy;

		FVector Location = (EnemyType + 1)*1000 * FVector(FMath::Cos(RandNum), FMath::Sin(RandNum), 0.f);
		switch (EnemyType) {
		case 0:
			tempEnemy = World->SpawnActor<ABaseEnemy>(Basic, Location, FRotator::ZeroRotator);
			break;
		case 1:
			tempEnemy = World->SpawnActor<ABaseEnemy>(Charger, Location, FRotator::ZeroRotator);
			break;
		case 2:
			tempEnemy = World->SpawnActor<ABaseEnemy>(SharpShooter, Location, FRotator::ZeroRotator);
			break;
		case 3:
			tempEnemy = World->SpawnActor<ABaseEnemy>(Boss, Location, FRotator::ZeroRotator);
			break;
		default:
			break;
		}

        EnemyArray.Add(tempEnemy);
	}
}

void ASpaceInvaderGameModeBase::OnEnemyDeath() {
	if (CurrentEnemyCount > 0) CurrentEnemyCount--;
}

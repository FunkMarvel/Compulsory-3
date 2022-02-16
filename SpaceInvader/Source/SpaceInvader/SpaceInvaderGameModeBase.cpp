// Copyright Epic Games, Inc. All Rights Reserved.


#include "SpaceInvaderGameModeBase.h"
#include "BaseEnemy.h"
#include "ShipPawn.h"
#include "GameHUD.h"
#include "Kismet/KismetMathLibrary.h"

ASpaceInvaderGameModeBase::ASpaceInvaderGameModeBase() {
	PrimaryActorTick.bCanEverTick = true;
}

void ASpaceInvaderGameModeBase::BeginPlay() {
	Super::BeginPlay();

	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
	AShipPawn* Player = Cast<AShipPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (Player) Player->OnPlayerDeath.AddDynamic(this, &ASpaceInvaderGameModeBase::OnPlayerDeath);

	SpawnWave();
}

void ASpaceInvaderGameModeBase::Tick(float DeltaTime) {
	if (CurrentEnemyCount <= 0 && CurrentWave < NumberOfWaves) {
		CurrentEnemyCount = 0;
		EnemyArray.Empty();
		CurrentWave++;
		SpawnWave();
	}
	else if (CurrentWave >= NumberOfWaves) {
		// end game.
	}
}

void ASpaceInvaderGameModeBase::SpawnEnemies(int32 EnemyType) {
	UWorld* World = GetWorld();
	float RandNum = FMath::FRandRange(0.f,UKismetMathLibrary::GetTAU());
	if (World) {
		ABaseEnemy* tempEnemy;

		FVector Location = (EnemyType) * 2000 * FVector(FMath::Cos(RandNum), FMath::Sin(RandNum), 0.f);
		switch (EnemyType) {
		case 2:
			tempEnemy = World->SpawnActor<ABaseEnemy>(Basic, Location, FRotator::ZeroRotator);
			break;
		case 1:
			tempEnemy = World->SpawnActor<ABaseEnemy>(Charger, Location, FRotator::ZeroRotator);
			break;
		case 3:
			tempEnemy = World->SpawnActor<ABaseEnemy>(SharpShooter, Location, FRotator::ZeroRotator);
			break;
		case 0:
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
	GEngine->AddOnScreenDebugMessage(-12, 2, FColor::Green, TEXT("Enemy died."));
}

void ASpaceInvaderGameModeBase::OnPlayerDeath() {
	AGameHUD* HUD = Cast<AGameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

	HUD->ViewGameOver(true);
}

void ASpaceInvaderGameModeBase::SpawnWave() {
	int32 EnemyType{2};

	switch (CurrentWave) {
	case 0:
		for (int i = 0; i < NumEnemiesWaveOne; i++) {
			SpawnEnemies(EnemyType);
			CurrentEnemyCount++;
			EnemyArray[i]->OnEnemyDiedDelegate.AddDynamic(this, &ASpaceInvaderGameModeBase::OnEnemyDeath);
		}
		break;
	case 1:
		for (int i = 0; i < NumEnemiesWaveTwo; i++) {
			if (i >= NumEnemiesWaveTwo/2) EnemyType = 3;
			SpawnEnemies(EnemyType);
			CurrentEnemyCount++;
			EnemyArray[i]->OnEnemyDiedDelegate.AddDynamic(this, &ASpaceInvaderGameModeBase::OnEnemyDeath);
		}
		break;
	case 2:
		for (int i = 0; i < NumEnemiesWaveThree; i++) {
			if (i >= 3*NumEnemiesWaveTwo/4) EnemyType = 3;
			else if (i >= NumEnemiesWaveTwo/2) EnemyType = 1;
			SpawnEnemies(EnemyType);
			CurrentEnemyCount++;
			EnemyArray[i]->OnEnemyDiedDelegate.AddDynamic(this, &ASpaceInvaderGameModeBase::OnEnemyDeath);
		}
		break;
	case 3:
		SpawnEnemies(0);
		CurrentEnemyCount++;
		EnemyArray[0]->OnEnemyDiedDelegate.AddDynamic(this, &ASpaceInvaderGameModeBase::OnEnemyDeath);
		break;
	default:
		break;
		}
}

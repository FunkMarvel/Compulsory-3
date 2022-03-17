// Copyright Epic Games, Inc. All Rights Reserved.


#include "SpaceInvaderGameModeBase.h"
#include "BaseEnemy.h"
#include "ShipPawn.h"
#include "GameHUD.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

ASpaceInvaderGameModeBase::ASpaceInvaderGameModeBase() {
	PrimaryActorTick.bCanEverTick = true;

	Levels.Add(TEXT("MainLevel"));
	Levels.Add(TEXT("FinalBossLevel"));
}

void ASpaceInvaderGameModeBase::BeginPlay() {
	Super::BeginPlay();
	
	FString CurrentMapName = GetWorld()->GetMapName();
	CurrentMapName.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);
	
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
	AShipPawn* Player = Cast<AShipPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
	
	if (Player) Player->OnPlayerDeath.AddDynamic(this, &ASpaceInvaderGameModeBase::OnPlayerDeath);
	
	if (CurrentMapName == Levels[0])
	{
		Score = 0;
		SpawnWave();
	}
	else
	{
		CurrentWave = 4;
		if (FinalBoss)
		{
			ABaseEnemy* TempEnemy = GetWorld()->SpawnActor<ABaseEnemy>(FinalBoss,
				FVector(20000.f,0.f,0.f), FRotator::ZeroRotator);

			TempEnemy->OnEnemyDiedDelegate.AddDynamic(this, &ASpaceInvaderGameModeBase::OnEnemyDeath);
			TempEnemy->SetEnemyIndex(0);
			EnemyArray.Add(TempEnemy);
			CurrentEnemyCount++;
		}
	}
}

void ASpaceInvaderGameModeBase::Tick(float DeltaTime) {
	if (CurrentEnemyCount <= 0 && CurrentWave < NumberOfWaves) {
		CurrentEnemyCount = 0;
		EnemyArray.Empty();
		CurrentWave++;
		SpawnWave();
	}
	else if (CurrentEnemyCount <= 0 && CurrentWave > NumberOfWaves) {
		AGameHUD* HUD = Cast<AGameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
		HUD->ViewGameWin(true);
	}
}

void ASpaceInvaderGameModeBase::SpawnEnemies(int32 EnemyType) {
	AGameHUD* HUD = Cast<AGameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
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
			//TODO set owner og Boss HealthBass
			HUD->GetBossHealthBar()->SetOwnerOfBar(tempEnemy);
			//HUD->GetBossHealthBar()->SetVisibility(ESlateVisibility::Visible);
			HUD->GetBossHealthBar()->ShowHealthBarBPEvent();
			break;
		default:
			break;
		}

		
        EnemyArray.Add(tempEnemy);

	}
}

void ASpaceInvaderGameModeBase::OnEnemyDeath(int32 Index) {
	EnemyArray[Index] = nullptr;
	if (CurrentEnemyCount > 0) CurrentEnemyCount--;
	GEngine->AddOnScreenDebugMessage(-12, 2, FColor::Green, TEXT("Enemy died."));
}

void ASpaceInvaderGameModeBase::OnPlayerDeath() {
	AGameHUD* HUD = Cast<AGameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	DisableInput(PlayerController);
	AShipPawn* Player = Cast<AShipPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
	Player->CapsuleComp->SetPhysicsLinearVelocity(FVector(0.f));
	Player->SetActorHiddenInGame(true);

	HUD->ViewGameOver(true);
}

void ASpaceInvaderGameModeBase::OnResetGamePress() {
	UGameplayStatics::OpenLevel(this, FName(*Levels[0]), false);
}

void ASpaceInvaderGameModeBase::SpawnWave() {
	int32 EnemyType{2};

	switch (CurrentWave) {
	case 0:
		for (int i = 0; i < NumEnemiesWaveOne; i++) {
			SpawnEnemies(EnemyType);
			CurrentEnemyCount++;
			EnemyArray[i]->OnEnemyDiedDelegate.AddDynamic(this, &ASpaceInvaderGameModeBase::OnEnemyDeath);
			EnemyArray[i]->SetEnemyIndex(i);
		}
		break;
	case 1:
		for (int i = 0; i < NumEnemiesWaveTwo; i++) {
			if (i >= NumEnemiesWaveTwo/2) EnemyType = 3;
			SpawnEnemies(EnemyType);
			CurrentEnemyCount++;
			EnemyArray[i]->OnEnemyDiedDelegate.AddDynamic(this, &ASpaceInvaderGameModeBase::OnEnemyDeath);
			EnemyArray[i]->SetEnemyIndex(i);
		}
		break;
	case 2:
		for (int i = 0; i < NumEnemiesWaveThree; i++) {
			if (i >= 3*NumEnemiesWaveTwo/4) EnemyType = 3;
			else if (i >= NumEnemiesWaveTwo/2) EnemyType = 1;
			SpawnEnemies(EnemyType);
			CurrentEnemyCount++;
			EnemyArray[i]->OnEnemyDiedDelegate.AddDynamic(this, &ASpaceInvaderGameModeBase::OnEnemyDeath);
			EnemyArray[i]->SetEnemyIndex(i);
		}
		break;
	case 3:
		SpawnEnemies(0);
		CurrentEnemyCount++;
		EnemyArray[0]->OnEnemyDiedDelegate.AddDynamic(this, &ASpaceInvaderGameModeBase::OnEnemyDeath);
		EnemyArray[0]->SetEnemyIndex(0);
		break;
	default:
		break;
		}
}

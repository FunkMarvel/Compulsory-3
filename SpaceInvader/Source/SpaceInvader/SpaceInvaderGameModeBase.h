// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MainGameInstance.h"
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
	ASpaceInvaderGameModeBase();

	void BeginPlay() override final;

	void Tick(float DeltaTime) override;

	void SpawnEnemies(int32 EnemyType);

	UPROPERTY(EditAnywhere, Category="Levels")
		TArray<FString> Levels;

private:
	UPROPERTY(EditAnywhere, Category = "Spawning|Enemies")
		TSubclassOf<class ABaseEnemy> Basic;

	UPROPERTY(EditAnywhere, Category = "Spawning|Enemies")
		TSubclassOf<class ABaseEnemy> SharpShooter;

	UPROPERTY(EditAnywhere, Category = "Spawning|Enemies")
		TSubclassOf<class ABaseEnemy> Charger;

	UPROPERTY(EditAnywhere, Category = "Spawning|Enemies")
		TSubclassOf<class ABaseEnemy> Boss;

	TArray<class ABaseEnemy*> EnemyArray;

	bool bAllDead;

	UPROPERTY(VisibleAnywhere, Category = "Spawning|Waves")
		int32 NumberOfWaves{3};
	int32 CurrentWave{};

	UPROPERTY(EditAnywhere, Category = "Spawning|Waves")
		int32 NumEnemiesWaveOne{5};

	UPROPERTY(EditAnywhere, Category = "Spawning|Waves")
		int32 NumEnemiesWaveTwo{10};

	UPROPERTY(EditAnywhere, Category = "Spawning|Waves")
		int32 NumEnemiesWaveThree{20};
	int32 CurrentEnemyCount{};

	UPROPERTY(EditAnywhere, Category="HUD|Score")
		int32 Score{};

	UFUNCTION()
		void OnEnemyDeath(int32 Index);

	UFUNCTION()
		void OnPlayerDeath();

	void SpawnWave();

public:
	TArray<class ABaseEnemy*> GetAllEnemies() { return EnemyArray; }

	UFUNCTION()
		void OnResetGamePress();
	
	int32 GetScore() const { return Score; }
	
	void AddScore(int32 DeltaScore);
};

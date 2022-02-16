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
	ASpaceInvaderGameModeBase();

	void BeginPlay() override final;

	void Tick(float DeltaTime) override;

	void SpawnEnemies(int32 EnemyType);

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
	UPROPERTY(EditAnywhere, Category = "Spawning|Waves")
		int32 NumEnemiesWaveOne{3};
	UPROPERTY(EditAnywhere, Category = "Spawning|Waves")
		int32 NumEnemiesWaveTwo{3};
	UPROPERTY(EditAnywhere, Category = "Spawning|Waves")
		int32 NumEnemiesWaveThree{3};

};

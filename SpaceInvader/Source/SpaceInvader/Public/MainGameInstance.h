

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MainGameInstance.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBroadCastScore, int32, Score);
/**
 * 
 */
UCLASS()
class SPACEINVADER_API UMainGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FBroadCastScore EventOnScoreChanged;
	
	UFUNCTION()
	void AddToScore(int Addition);
	UFUNCTION()
	void SetScore(int newScore);
	UFUNCTION()
	int32 GetScore() const {return Score; }

	UFUNCTION()
	void SetPlayerStats(int32 Health, int32 Ammo, int32 Dash);

	UFUNCTION()
	int32 GetPlayerHealth() const {return PlayerHealth; }
	UFUNCTION()
	int32 GetPlayerAmmo() const {return PlayerAmmo; }
	UFUNCTION()
	int32 GetPlayerDash() const {return PlayerDash; }
private:
	
	int32 Score = 0;

	//player stats
	int32 PlayerHealth = 5;
	int32 PlayerAmmo = 0;
	int32 PlayerDash = 0;
};

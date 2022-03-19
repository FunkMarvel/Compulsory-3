

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
	void SetPlayerStats(float Health, int32 Ammo, int32 Dash, float StamiaTimer);

	UFUNCTION()
	float GetPlayerHealth() const {return PlayerHealth; }
	UFUNCTION()
	int32 GetPlayerAmmo() const {return PlayerAmmo; }
	UFUNCTION()
	int32 GetStamina() const {return PlayerDash; }
	UFUNCTION()
	float GetPlayerStaminaTimer() const {return PlayerStaminaTimer; }
private:
	
	int32 Score = 0;

	//player stats
	float PlayerHealth = 50;
	int32 PlayerAmmo = 0;
	int32 PlayerDash = 0;
	float PlayerStaminaTimer = 0.f;
};

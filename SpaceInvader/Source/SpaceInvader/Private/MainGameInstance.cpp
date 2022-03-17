


#include "MainGameInstance.h"

void UMainGameInstance::AddToScore(int Addition)
{
	Score += Addition;
	EventOnScoreChanged.Broadcast(Score);
}

void UMainGameInstance::SetScore(int newScore)
{
	Score = newScore;
	EventOnScoreChanged.Broadcast(Score);
}

void UMainGameInstance::SetPlayerStats(float Health, int32 Ammo, int32 Dash, float StaminaTimer)
{
	PlayerHealth = Health;
	PlayerAmmo = Ammo;
	PlayerDash = Dash;
	PlayerStaminaTimer = StaminaTimer;
}

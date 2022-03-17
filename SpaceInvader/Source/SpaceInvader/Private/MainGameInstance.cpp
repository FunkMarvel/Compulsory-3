


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

void UMainGameInstance::SetPlayerStats(int32 Health, int32 Ammo, int32 Dash)
{
	PlayerHealth = Health;
	PlayerAmmo = Ammo;
	PlayerDash = Dash;
}

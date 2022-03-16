

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MainGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SPACEINVADER_API UMainGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	
	UFUNCTION()
	void AddToScore(int Addition){ Score += Addition; }
	UFUNCTION()
	void SetScore(int newScore){Score = newScore; }
	UFUNCTION()
	int32 GetScore() const {return Score; }
private:
	
	int32 Score = 0;
};

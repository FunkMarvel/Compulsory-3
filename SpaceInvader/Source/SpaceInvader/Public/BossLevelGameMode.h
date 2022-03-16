

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BossLevelGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SPACEINVADER_API ABossLevelGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABossLevelGameMode();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning|Boss")
		TSubclassOf<class ABaseEnemy> FinalBossClass;

protected:
	void BeginPlay() override final;

	void Tick(float DeltaTime) override;
};

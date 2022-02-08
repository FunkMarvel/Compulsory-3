

#pragma once

#include "CoreMinimal.h"
#include "BaseEnemy.h"
#include "BasicShooterEnemy.generated.h"

/**
 * 
 */
UCLASS()
class SPACEINVADER_API ABasicShooterEnemy : public ABaseEnemy
{
	GENERATED_BODY()
	
//my desegnated area

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;



private:
	
};

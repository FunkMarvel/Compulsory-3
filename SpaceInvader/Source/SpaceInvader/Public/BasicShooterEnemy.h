
#pragma once

#include "CoreMinimal.h"
#include "BaseEnemy.h"
#include "BasicShooterEnemy.generated.h"


UCLASS()
class SPACEINVADER_API ABasicShooterEnemy : public ABaseEnemy
{
	GENERATED_BODY()

public:
	ABasicShooterEnemy();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	
	FTimerHandle FireRateTimerHandle;

	float FireRate = 2.f;
};

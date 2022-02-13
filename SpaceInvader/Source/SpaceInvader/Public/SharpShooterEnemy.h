

#pragma once

#include "CoreMinimal.h"
#include "BaseEnemy.h"
#include "SharpShooterEnemy.generated.h"

/**
 * 
 */
UCLASS()
class SPACEINVADER_API ASharpShooterEnemy : public ABaseEnemy
{
	GENERATED_BODY()
	
public:
	ASharpShooterEnemy();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;


private:


	float LastShotTime = 0.f;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Enemy")
		float ShotInterval = 0.7f;
};



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

	// My Deseg ----------
public:

	// by how much before the shot we should play the sound (sharpshooter has a windup sound)
	UPROPERTY(EditDefaultsOnly, Category = "Enemy|SoundOffset")
		float SoundOffset = 0.f;
	bool bPlayedSound = false;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
};

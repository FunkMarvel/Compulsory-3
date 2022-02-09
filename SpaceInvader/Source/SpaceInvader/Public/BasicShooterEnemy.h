
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

	virtual void MoveLogic() override;

	virtual void FiringLogic() override;

private:
	

	float LastShotTime = 0.f;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Enemy")
	float ShotInterval = 0.7f;
};


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

	UPROPERTY(EditDefaultsOnly, Category = "Enemy")
		class UStaticMeshComponent* SpinnerMesh;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, Category = "Enemy")
		float SpinnerSpinSpeed = 14.f;

protected:
	virtual void BeginPlay() override;

;

private:
	
	UFUNCTION()
	void SpinSpinner(float SpinSpeed);

	/*float LastShotTime = 0.f;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Enemy")
	float ShotInterval = 0.7f;*/
};

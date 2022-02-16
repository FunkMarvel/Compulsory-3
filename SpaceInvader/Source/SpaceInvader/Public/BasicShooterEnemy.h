
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


	// Gun barrel mesh
	UPROPERTY(EditDefaultsOnly, Category = "Enemy")
		class UStaticMeshComponent* SpinnerMesh;
	UPROPERTY(EditDefaultsOnly, Category = "Enemy")
		float SpinnerSpinSpeed = 14.f;



protected:
	virtual void BeginPlay() override;

private:

	UFUNCTION()
	void SpinSpinner(float SpinSpeed);
};



#pragma once

#include "CoreMinimal.h"
#include "BaseEnemy.h"
#include "ChargerEnemy.generated.h"

/**
 * 
 */
UCLASS()
class SPACEINVADER_API AChargerEnemy : public ABaseEnemy
{
	GENERATED_BODY()
public:
	AChargerEnemy();
	virtual void Tick(float DeltaTime) override;
private:
protected:

	
	virtual void MoveLogic() override;
//
//	//my deseg
public:
	//components
	UPROPERTY(EditAnywhere, Category = "Enemy")
		class UStaticMeshComponent* BladesMesh;

	//charging
	enum ChargerState {
		Moving,
		WindUp,
		Charging
	};
	ChargerState currentState;
//
	UPROPERTY(EditAnywhere, Category = "Enemy | CustomMovment")
	float NormalSpeed;
	UPROPERTY(EditAnywhere, Category = "Enemy | CustomMovment")
	float ChargeSpeed;
	UPROPERTY(EditAnywhere, Category = "Enemy | CustomMovment")
	float WindupSpeed;

	UPROPERTY(EditAnywhere, Category = "Enemy | BladeSpinningSpeed")
	float BladeNormalSpeed;
	UPROPERTY(EditAnywhere, Category = "Enemy | BladeSpinningSpeed")
	float BladeChargeSpeed;
	UPROPERTY(EditAnywhere, Category = "Enemy | BladeSpinningSpeed")
	float BladeWindupSpeed;

	//funcs
	UFUNCTION()
		void SpinBlades();
	
};

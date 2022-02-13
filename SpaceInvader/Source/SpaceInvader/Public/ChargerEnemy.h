

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
	void CurrentStateLogic();

	//charger Velocity
	FVector ChargeVelocity = FVector::ZeroVector;
	
	//Windup and target found
	bool bFoundTarget = false;
	float WindUpTime = 2.f;
	float ChargingMinimumTime = 1.2f;
	float CurrentWindUpTime = 0.f;
	
	//tilt stuff
	float TargetTilt = 0.f;

protected:

	
	
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
	// Movemnt speed
	UPROPERTY(EditAnywhere, Category = "Enemy | CustomMovment")
	float NormalSpeed;
	UPROPERTY(EditAnywhere, Category = "Enemy | CustomMovment")
	float ChargeSpeed;
	UPROPERTY(EditAnywhere, Category = "Enemy | CustomMovment")
	float WindupSpeed;

	//blade speed
	UPROPERTY(EditAnywhere, Category = "Enemy | BladeSpinningSpeed")
	float BladeNormalSpeed;
	UPROPERTY(EditAnywhere, Category = "Enemy | BladeSpinningSpeed")
	float BladeChargeSpeed;
	UPROPERTY(EditAnywhere, Category = "Enemy | BladeSpinningSpeed")
	float BladeWindupSpeed;

	UPROPERTY(EditAnywhere, Category = "Enemy | TiltAmount")
		float NormalTilt;
	UPROPERTY(EditAnywhere, Category = "Enemy | TiltAmount")
		float WindUpTilt;
	UPROPERTY(EditAnywhere, Category = "Enemy | TiltAmount")
		float ChargeTilt;
	

	//funcs
	UFUNCTION()
		void SpinBlades();
	
};

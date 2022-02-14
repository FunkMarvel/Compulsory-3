

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
	void OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult) override;
	
	
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
		Charging,
		CoolDown
	};
	ChargerState currentState;

	float StateTime = 0.f;


	UFUNCTION()
	void MovingState();


	//Wind Up
	UFUNCTION()
	void WindUpState();
	UPROPERTY(EditAnywhere, Category = "Enemy | WindUp")
	float WindUpTime;

	//Charge
	UFUNCTION()
	void ChargingState();
	FVector ChargeVelocity = FVector::ZeroVector;
	UPROPERTY(EditAnywhere, Category = "Enemy | Charge")
	float ChargeTime;



	UFUNCTION()
	void CoolDownState();

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

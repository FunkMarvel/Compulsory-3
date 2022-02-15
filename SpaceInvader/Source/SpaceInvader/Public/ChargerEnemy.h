

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
	//sound
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Enemy|Audio")
		USoundBase* WindUpSound = nullptr;

	//components
	UPROPERTY(EditDefaultsOnly, Category = "Enemy")
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
	UPROPERTY(EditDefaultsOnly, Category = "Enemy|WindUp")
	float WindUpTime;

	//Charge
	UFUNCTION()
	void ChargingState();
	FVector ChargeVelocity = FVector::ZeroVector;
	UPROPERTY(EditDefaultsOnly, Category = "Enemy|Charge")
	float ChargeTime;

	//CoolDOwn
	UFUNCTION()
	void CoolDownState();
	UPROPERTY(EditDefaultsOnly, Category = "Enemy|CoolDown")
		float CoolDownTime;

	// Movemnt speed
	UPROPERTY(EditDefaultsOnly, Category = "Enemy|CustomMovment")
	float NormalSpeed;
	UPROPERTY(EditDefaultsOnly, Category = "Enemy|CustomMovment")
	float ChargeSpeed;
	UPROPERTY(EditDefaultsOnly, Category = "Enemy|CustomMovment")
	float WindupSpeed;
	UPROPERTY(EditDefaultsOnly, Category = "Enemy|CustomMovment")
	float CoolDownSpeed;
	

	//blade speed
	UPROPERTY(EditDefaultsOnly, Category = "Enemy|BladeSpinningSpeed")
	float BladeNormalSpeed;
	UPROPERTY(EditDefaultsOnly, Category = "Enemy|BladeSpinningSpeed")
	float BladeChargeSpeed;
	UPROPERTY(EditDefaultsOnly, Category = "Enemy|BladeSpinningSpeed")
	float BladeWindupSpeed;
	UPROPERTY(EditDefaultsOnly, Category = "Enemy|BladeSpinningSpeed")
	float BladeCoolDownSpeed;
	


	UPROPERTY(EditDefaultsOnly, Category = "Enemy|TiltAmount")
	float NormalTilt;
	UPROPERTY(EditDefaultsOnly, Category = "Enemy|TiltAmount")
	float WindUpTilt;
	UPROPERTY(EditDefaultsOnly, Category = "Enemy|TiltAmount")
	float ChargeTilt;
	UPROPERTY(EditDefaultsOnly, Category = "Enemy|TiltAmount")
	float CoolDownTilt;
	
	

	//funcs
	UFUNCTION()
		void SpinBlades();
	
};

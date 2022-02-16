

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

	
	//my deseg ----------------------------
public:
	//Propeller Mesh
	UPROPERTY(EditDefaultsOnly, Category = "Enemy")
		class UStaticMeshComponent* BladesMesh;

	//When charger hits something
	void OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult) override;

	//sound
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Enemy|Audio")
		USoundBase* WindUpSound = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Enemy|Audio")
		USoundBase* OnHitSound = nullptr;

	//charging states
	enum ChargerState {
		Moving,
		WindUp,
		Charging,
		CoolDown
	};
	ChargerState currentState;

	//the time we have been in one state
	float StateTime = 0.f;

	// moving state
	UFUNCTION()
	void MovingState();

	//Wind Up state
	UFUNCTION()
	void WindUpState();
	UPROPERTY(EditDefaultsOnly, Category = "Enemy|WindUp")
	float WindUpTime;

	//Charge state
	UFUNCTION()
	void ChargingState();
	FVector ChargeVelocity = FVector::ZeroVector;
	UPROPERTY(EditDefaultsOnly, Category = "Enemy|Charge")
	float ChargeTime;

	//Cooldown
	UFUNCTION()
	void CoolDownState();
	UPROPERTY(EditDefaultsOnly, Category = "Enemy|CoolDown")
		float CoolDownTime;

	// movemnt speed
	UPROPERTY(EditDefaultsOnly, Category = "Enemy|CustomMovment")
	float NormalSpeed;
	UPROPERTY(EditDefaultsOnly, Category = "Enemy|CustomMovment")
	float ChargeSpeed;
	UPROPERTY(EditDefaultsOnly, Category = "Enemy|CustomMovment")
	float WindupSpeed;
	UPROPERTY(EditDefaultsOnly, Category = "Enemy|CustomMovment")
	float CoolDownSpeed;
	

	// blade speed
	UPROPERTY(EditDefaultsOnly, Category = "Enemy|BladeSpinningSpeed")
	float BladeNormalSpeed;
	UPROPERTY(EditDefaultsOnly, Category = "Enemy|BladeSpinningSpeed")
	float BladeChargeSpeed;
	UPROPERTY(EditDefaultsOnly, Category = "Enemy|BladeSpinningSpeed")
	float BladeWindupSpeed;
	UPROPERTY(EditDefaultsOnly, Category = "Enemy|BladeSpinningSpeed")
	float BladeCoolDownSpeed;
	

	// tilt amount
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

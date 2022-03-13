// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "Enums.h"

#include "ShipPawn.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerDeathDelegate);

UCLASS()
class SPACEINVADER_API AShipPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AShipPawn();
	bool GetDashState() { return bDashing; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FPlayerDeathDelegate OnPlayerDeath;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Mesh")
		class UStaticMeshComponent* PlayerMesh{nullptr};

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Mesh")
		class UStaticMeshComponent* PointerMesh{ nullptr };

	UPROPERTY(VisibleAnywhere, Category = "Collider")
		class UCapsuleComponent* CapsuleComp{nullptr};

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Camera")
		class USpringArmComponent* CameraArm{nullptr};

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Camera")
		class UCameraComponent* Camera{nullptr};

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Movement")
		float Acceleration{ 50000.f };

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Movement")
		float SpeedLimit{ 2500.f };

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Player")
		int32 MaxAmmo{ 30 };
	int32 Ammo{MaxAmmo};

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Player")
		float MaxHealth{ 50 };
	float Health{ MaxHealth };

	UPROPERTY(EditAnywhere, Category = "Movement")
		float StaminaRechargeTime{5.f};
	float StaminaTimer{StaminaRechargeTime};

	UPROPERTY(EditAnywhere, Category = "Movement")
		int32 MaxStamina{3};
	int32 Stamina{MaxStamina};

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Sound|Combat")
		class USoundBase* ShootingSound{nullptr};

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Sound|Combat")
		class USoundBase* AmmoWarning{ nullptr };

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Sound|Combat")
		class USoundBase* ReloadingSound{nullptr};

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Sound|Movement")
		class USoundBase* DashSound{ nullptr };

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Sound|Movement")
		class USoundBase* DashRechargeSound{ nullptr };

	// Firing
	UPROPERTY(EditAnywhere, Category = "Combat")
		float ProjectileForwardOffset{200.f};
	UPROPERTY(EditAnywhere, Category = "Combat")
		float ProjectileSpeed{3000.f};

		// Reload relevant
	UPROPERTY(EditDefaultsOnly ,Category = "Combat|Reload")
	float StartReloadingTime = 1.f;
	UPROPERTY(EditDefaultsOnly ,Category = "Combat|Reload")
	float ReloadTimePeriod = 0.06f;
	UPROPERTY(EditDefaultsOnly ,Category = "Combat|Reload")
	float ReloadTime = 0.f;
	bool bReloadFirstFrame = false;
	
	
	
	UFUNCTION()
		void OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult);

	void HandleShooting();
	void StartReload();
	void Shoot();
	void Shoot(FVector FireLocation, float Angle);
	void StartShooting();
	void EndShooting();


	//shotgun firing
	UFUNCTION()
	void SetCurrentFireState(EPlayerFireState NewFireState);
	
	UPROPERTY(EditAnywhere, Category = "Combat|Fire")
	class UArrowComponent* LeftFireArrowComponent{nullptr};
	UPROPERTY(EditAnywhere, Category = "Combat|Fire")
	class UArrowComponent* RightFireArrowComponent{nullptr};

	UPROPERTY(EditAnywhere, Category = "Combat|Fire")
	class USkeletalMeshComponent* LeftTurretSkeletalMeshComponent{nullptr};
	UPROPERTY(EditAnywhere, Category = "Combat|Fire")
	class USkeletalMeshComponent* RightTurretSkeletalMeshComponent{nullptr};

	UPROPERTY(EditAnywhere, Category = "Animations")
	class UAnimationAsset* DeployTurretAnimationAsset{nullptr};
	UPROPERTY(EditAnywhere, Category = "Animations")
	class UAnimationAsset* RetractTurretAnimationAsset{nullptr};

	
private:
	// shotgun firing
	UPROPERTY(meta = (AllowPrivateAccess = "true") ,EditAnywhere, Category = "Fire|Shotgun")
	EPlayerFireState ECurrentFireState = EPlayerFireState::Normal;
	UPROPERTY(meta = (AllowPrivateAccess = "true") ,EditAnywhere, Category = "Fire|Shotgun")
	float MultiShotAngle = 5.f;
	
	UPROPERTY(meta = (AllowPrivateAccess = "true") ,EditAnywhere, Category = "Fire|Shotgun")
	float NormalShootProjectileSpeed{4500.f};
	UPROPERTY(meta = (AllowPrivateAccess = "true") ,EditAnywhere, Category = "Fire|Shotgun")
	float MultiShootProjectileSpeed{2000.f};
	
	// pointer mesh
	void PointPointerMesh();
	FVector CurrentPointerVec = FVector::ZeroVector;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
		TSubclassOf<class AProjectile> ProjectileClass;

	FVector InitLocation = FVector::ZeroVector;

	void MoveXAxis(float Value);
	void MoveYAxis(float Value);

	void Aim(float Value);

	void Dash();
	void Focus();
	bool bFocus{true};

	float XValue{};
	float YValue{};

	UPROPERTY(EditAnywhere, Category = "Movement")
		float DashDuration{1.f};
	
	UPROPERTY(EditAnywhere, Category = "Movement")
		float DashRotation{360.f};
	float DashTimer{DashDuration};

	UPROPERTY(EditAnywhere, Category = "Movement")
		float FocusSpeedMod{ 0.5f };

	UPROPERTY(EditAnywhere, Category = "Combat")
		float TimeBetweenShots{ 0.25f };
	float ShotTimer{};
	float LastShotTimer{};

	bool bFocused{ false };
	bool bDashing{ false };
	bool bShooting{ false };
};

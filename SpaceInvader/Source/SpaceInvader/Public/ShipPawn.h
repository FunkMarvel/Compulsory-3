// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ShipPawn.generated.h"

UCLASS()
class SPACEINVADER_API AShipPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AShipPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
		class UStaticMeshComponent* PlayerMesh{nullptr};

	UPROPERTY(VisibleAnywhere, Category = "Collider")
		class UCapsuleComponent* CapsuleComp{nullptr};

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Camera")
		class USpringArmComponent* SpringArm{nullptr};

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Camera")
		class UCameraComponent* Camera{nullptr};

	UPROPERTY(VisibleAnywhere, Category = "Overlay")
		class UWidgetComponent* HealthWidgetComp;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Movement")
		float Acceleration{ 100000.f };

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Movement")
		float SpeedLimit{ 2000.f };

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Player")
		int32 Ammo{ 30 };

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Player")
		float Health{ 150 };

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Player")
		float MaxHealth{ 150 };

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Sound")
		class USoundBase* ShootingSound{nullptr};

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Sound")
		class USoundBase* ReloadingSound{nullptr};

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Player")
		TSubclassOf<AActor> ActorToSpawn;

	// Firing
	UPROPERTY(EditAnywhere, Category = "Combat")
		float ProjectileForwardOffset{185.f};

	UPROPERTY(EditAnywhere, Category = "Combat")
		float ProjectileSpeed{2500.f};

	UFUNCTION()
		void OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult);

	void Reload();
	void Shoot();
	void StartShooting();
	void EndShooting();

	UFUNCTION(BluePrintCallable)
		void ResetLoaction() const;
	bool InContact;

private:
	
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
		TSubclassOf<class AProjectile> ProjectileClass;

	FVector InitLocation = FVector::ZeroVector;

	void MoveXAxis(float Value);
	void MoveYAxis(float Value);

	void Aim(float Value);

	void Dash();
	void Focus(float Value);

	UFUNCTION()
		void Death();

	float XValue{};
	float YValue{};
	
	UPROPERTY(EditAnywhere, Category = "Movement")
		float DashDuration{1};
	
	UPROPERTY(EditAnywhere, Category = "Movement")
		float DashRotation{360};
	
	float DashTimer{DashDuration};

	UPROPERTY(EditAnywhere, Category = "Movement")
		float FocusSpeedMod{ 0.5f };

	UPROPERTY(EditAnywhere, Category = "Combat")
		float TimeBetweenShots{ 0.5f };
	float ShotTimer{};

	bool bFocused{ false };
	bool bDashing{ false };
	bool bShooting{ false };
};

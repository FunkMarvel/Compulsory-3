// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
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

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "PlayerMesh")
		UStaticMeshComponent* PlayerMesh{nullptr};

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "PlayerMesh")
		USpringArmComponent* SpringArm{nullptr};

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "PlayerMesh")
		UCameraComponent* Camera{nullptr};

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "PlayerMesh")
		float Speed{5.f};

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "PlayerMesh")
		int Ammo{30};

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "PlayerMesh")
		USoundBase* ShootingSound{nullptr};

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "PlayerMesh")
		USoundBase* ReloadingSound{nullptr};

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "PlayerMesh")
		TSubclassOf<AActor> ActorToSpawn;

	void Reload();
	void Shoot();

	UFUNCTION(BluePrintCallable)
		void ResetLoaction() const;
	bool InContact;

private:
	FVector InitLocation = FVector::ZeroVector;


	void MoveXAxis(float Value);
	void MoveYAxis(float Value);

	void Dash();
	float XValue = 0.f;
	float YValue = 0.f;
	float DashTimer = 0.f;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class SPACEINVADER_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Components
	UPROPERTY(EditDefaultsOnly, Category = "Bullet")
		UStaticMeshComponent* ProjectileMesh;

	// Movment Component
	UPROPERTY(VisibleAnywhere, Category = "Movment")
		class UProjectileMovementComponent* ProjectileMovmentComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Bullet")
		float Damage = 1.f;

	UPROPERTY(EditDefaultsOnly, Category = "Bullet")
		float MaxTimeAlive = 4.f;

	// Particle System
	UPROPERTY(EditDefaultsOnly, Category = "Bullet")
		class UParticleSystemComponent* Trail = nullptr;

	
	float TimeAlive = 0.f;
	UFUNCTION()
		virtual void OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// FX
	UPROPERTY(EditDefaultsOnly, Category = "Bullet")
		class UParticleSystem* ParticleSystemHit;
	UFUNCTION()
		void SpawnOnHitFX();


};

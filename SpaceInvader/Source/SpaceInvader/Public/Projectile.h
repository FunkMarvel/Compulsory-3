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

	UPROPERTY(EditDefaultsOnly, Category = "Bullet")
		UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(VisibleAnywhere, Category = "Movment")
		class UProjectileMovementComponent* ProjectileMovmentComponent;

	UPROPERTY(EditAnywhere, Category = "Bullet")
		float Damage = 1.f;

	UPROPERTY(EditAnywhere, Category = "Bullet")
		float MaxTimeAlive = 4.f;

	/*UPROPERTY(EditAnywhere, Category = "Bullet")
		AActor* Parent = nullptr;*/

private:

	UFUNCTION()
		void OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	float TimeAlive = 0.f;
};

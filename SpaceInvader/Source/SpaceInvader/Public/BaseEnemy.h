

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseEnemy.generated.h"

UCLASS()
class SPACEINVADER_API ABaseEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	


	// my desegnater area -----------------------------
public:
	// components
	UPROPERTY(EditAnywhere, Category = "Enemy")
		class UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, Category = "Collider")
		class UCapsuleComponent* CapsuleComp = nullptr;


	// Basic Variables
	UPROPERTY(EditAnywhere, Category = "Enemy")
		float StartHealth;
	UPROPERTY(EditAnywhere, Category = "Enemy")
		float MovmentSpeed;
	UPROPERTY(EditAnywhere, Category = "Enemy")
		float ProjectileForwardOffset;
	UPROPERTY(EditAnywhere, Category = "Enemy")
	float currentTilt = 20.f;

	//AI LOGIC
	UPROPERTY(EditAnywhere, Category = "Enemy")
		float InnerRange;
	UFUNCTION()
		bool IsInInnerRange();
	
	
	// Firing
	UPROPERTY(EditAnywhere, Category = "Enemy")
		float ProjectileSpeed = 1100.f;


private:


protected:
	float LastShotTime = 0.f;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Enemy")
		float ShotInterval = 0.7f;
	
	APawn* PlayerPawn = nullptr;
	int Health;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
		TSubclassOf<class AProjectile> ProjectileClass;


	

	UFUNCTION()
	void RotateMeshAfterMovment(UStaticMeshComponent* Comp, FVector Direction);

	UFUNCTION()
	void OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void FireAtPlayer();

	UFUNCTION()
	void FireInDirection(FVector Direction);

	

	// Move functuon Direction is in world space
	UFUNCTION()
	void Move(FVector Direction);
	// Look at PLayer
	UFUNCTION()
	void LookAtPlayer();

	//move the enemy left to right
	float GetLeftRightMovment(const float& _Amplitude, const float& _Lambda);

	FVector GetToPlayerDirection();

	float CurrentMovmentTime = 0.f;
	UPROPERTY(EditAnywhere, Category = "Enemy | LeftRightMovment")
		float Amplitude = 4.f;
	UPROPERTY(EditAnywhere, Category = "Enemy | LeftRightMovment")
		float Lambda = 1.f;
	
};

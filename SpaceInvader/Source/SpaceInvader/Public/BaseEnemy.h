

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
	UPROPERTY(EditDefaultsOnly, Category = "Enemy")
		class UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, Category = "Collider")
		class UCapsuleComponent* CapsuleComp = nullptr;


	// Basic Variables
	UPROPERTY(EditDefaultsOnly, Category = "Enemy")
		float StartHealth;
	UPROPERTY(EditDefaultsOnly, Category = "Enemy")
		float MovmentSpeed;
	UPROPERTY(EditDefaultsOnly, Category = "Enemy")
		float ProjectileForwardOffset;
	UPROPERTY(EditDefaultsOnly, Category = "Enemy")
	float currentTilt = 20.f;

	//AI LOGIC
	UPROPERTY(EditDefaultsOnly, Category = "Enemy")
		float InnerRange;
	UFUNCTION()
		bool IsInInnerRange();
	
	
	// Firing
	UPROPERTY(EditDefaultsOnly, Category = "Enemy")
		float ProjectileSpeed = 1100.f;


	//sound
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Enemy|Audio")
		USoundBase* FiringSound = nullptr;
	UFUNCTION()
		void PlayFireSound();
	float StartSoundTime = 0.f;
private:


protected:
	float LastShotTime = 0.f;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"), Category = "Enemy")
		float ShotInterval = 0.7f;
	
	APawn* PlayerPawn = nullptr;
	int Health;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
		TSubclassOf<class AProjectile> ProjectileClass;


	

	UFUNCTION()
	void RotateMeshAfterMovment(UStaticMeshComponent* Comp, FVector Direction);

	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
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
	

	FVector GetToPlayerDirection();

	
	
};



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

	// Basic Components
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

	//AI 
	UPROPERTY(EditDefaultsOnly, Category = "Enemy")
		float InnerRange;
	UFUNCTION()
		bool IsInInnerRange();
	
	
	// Firing
	UPROPERTY(EditDefaultsOnly, Category = "Enemy")
		float ProjectileSpeed = 1100.f;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"), Category = "Enemy")
		float ShotInterval = 0.7f;

	//sound
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Enemy|Audio")
		USoundBase* FiringSound = nullptr;
	UFUNCTION()
		void PlayFireSound();
	float StartSoundTime = 0.f;

	
private:


protected:

	float LastShotTime = 0.f;
	int Health;
	APawn* PlayerPawn = nullptr;

	//projectile
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
		TSubclassOf<class AProjectile> ProjectileClass;

	//FX
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Enemy|FX")
		TSubclassOf<class ASpawnParticleEffectActor> ParticleActorToSpawnClass;
	UFUNCTION()
		void PlayDeathFX();

	// On Hit
	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);

	// Movment and Compant Relevent funcs
	UFUNCTION()
	void RotateMeshAfterMovment(UStaticMeshComponent* Comp, FVector Direction);

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
	
	UFUNCTION()
	FVector GetToPlayerDirection();

	
	
};

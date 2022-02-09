

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
	
	// my desegnater area
public:
	UPROPERTY(EditAnywhere, Category = "Enemy")
		class UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, Category = "Collider")
		class UCapsuleComponent* CapsuleComp = nullptr;

	UPROPERTY(EditAnywhere, Category = "Enemy")
		int StartHealth;
	UPROPERTY(EditAnywhere, Category = "Enemy")
		float MovmentSpeed;
	UPROPERTY(EditAnywhere, Category = "Enemy")
		float ProjectileForwardOffset;

	//AI LOGIC
	UPROPERTY(EditAnywhere, Category = "Enemy")
		float AggroRange;
	UFUNCTION()
		bool IsInAgroRange();
	UPROPERTY(EditAnywhere, Category = "Enemy")
		float InnerRange;
	UFUNCTION()
		bool IsInInnerRange();
	
	// Firing
	UPROPERTY(EditAnywhere, Category = "Enemy")
		float ProjectileSpeed = 1100.f;


protected:

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
		TSubclassOf<class AProjectile> ProjectileClass;

	APawn* PlayerPawn = nullptr;

	int Health;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
		void FireAtPlayer();

	//should be called every frame in tick
	UFUNCTION()
		virtual void MoveLogic(){}

	//should be called every frame in tick
	UFUNCTION()
		virtual void FiringLogic() {}


	/// <summary>
	/// Move functuon Direction is in world space
	/// </summary>
	void Move(const FVector& Direction);

	void LookAtPlayer();

	
};

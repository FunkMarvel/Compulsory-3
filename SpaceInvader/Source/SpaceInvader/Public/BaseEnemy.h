

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
		void OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, 
			const FHitResult & SweepResult);
	
	UFUNCTION()
		void FireAtPlayer();

	//should be called every frame in tick
	UFUNCTION()
		virtual void MoveLogic(){}

	//should be called every frame in tick
	UFUNCTION()
		virtual void FiringLogic() {}


	// Move functuon Direction is in world space
	void Move(FVector Direction);

	void LookAtPlayer();

	//move the enemy left to right
	float GetLeftRightMovment(const float& _Amplitude, const float& _Lambda);
	float CurrentMovmentTime = 0.f;
	UPROPERTY(EditAnywhere, Category = "Enemy | LeftRightMovment")
		float Amplitude = 4.f;
	UPROPERTY(EditAnywhere, Category = "Enemy | LeftRightMovment")
		float Lambda = 1.f;
	
};

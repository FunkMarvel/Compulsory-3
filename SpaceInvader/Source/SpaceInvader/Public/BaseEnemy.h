

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

protected:

	int Health;
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/// <summary>
	/// Move functuon Direction is in world space
	/// </summary>
	void Move(const FVector& Direction);

	void LookAtPlayer();

	
};

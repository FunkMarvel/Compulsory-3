

#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "EnemyProjectile.generated.h"

/**
 * 
 */
UCLASS()
class SPACEINVADER_API AEnemyProjectile : public AProjectile
{
	GENERATED_BODY()
public:
	AEnemyProjectile();

private:
	virtual void OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};

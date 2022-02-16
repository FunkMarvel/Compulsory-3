

#include "EnemyProjectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "BaseEnemy.h"
#include "ShipPawn.h"

AEnemyProjectile::AEnemyProjectile() {

}



void AEnemyProjectile::BeginPlay()
{
	Super::BeginPlay();
	//ProjectileMesh->OnComponentBeginOverlap.AddDynamic(this, &AEnemyProjectile::OnHit);
}

void AEnemyProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyProjectile::OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//guard cloauses
	if (OtherActor->IsA<AEnemyProjectile>() || OtherActor->IsA<ABaseEnemy>())
	{
		return;
	}

	if(OtherActor->IsA<AShipPawn>())
	{
		AShipPawn* Ship = Cast<AShipPawn>(OtherActor); 
		if (!Ship->GetDashState())	// If ship is dashing do nothing
		{
			SpawnOnHitFX();
			Destroy();
		}
	}
	else
	{
		Destroy();
		SpawnOnHitFX();
	}
}
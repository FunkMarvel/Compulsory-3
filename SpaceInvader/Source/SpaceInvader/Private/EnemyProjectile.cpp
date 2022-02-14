

#include "Components/StaticMeshComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "EnemyProjectile.h"

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
	if (OtherActor->IsA<AEnemyProjectile>())
	{

	}
	else
	{
		Destroy();
	}
}
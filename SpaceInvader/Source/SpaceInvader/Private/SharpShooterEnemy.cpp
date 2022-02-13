

#include "Kismet/GameplayStatics.h"
#include "SharpShooterEnemy.h"

ASharpShooterEnemy::ASharpShooterEnemy() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileForwardOffset = 100.f;
	ShotInterval = 2.f;
	MovmentSpeed = 100.f;
	InnerRange = 700.f;
	ProjectileSpeed = 7000.f;
	StartHealth = 7.f;
}


void ASharpShooterEnemy::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	
	//Enemy logic
	FVector Direction = GetToPlayerDirection().GetSafeNormal();
	if (IsInInnerRange())
	{
		Direction = -Direction;
	}
	Move(Direction);
	RotateMeshAfterMovment(Mesh, Direction);


	

	LookAtPlayer();
}

void ASharpShooterEnemy::BeginPlay() {
	Super::BeginPlay();



}



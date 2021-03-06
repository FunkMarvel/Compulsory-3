

#include "SharpShooterEnemy.h"
#include "Kismet/GameplayStatics.h"

ASharpShooterEnemy::ASharpShooterEnemy() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Basic Variables
	ProjectileForwardOffset = 100.f;
	ShotInterval = 2.f;
	SoundOffset = 1.7f;
	MovmentSpeed = 100.f;
	InnerRange = 1400.f;
	FireRange = 3000.f;
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

	// shooting logic
	if (IsInFireRange())
	{
		LastShotTime += UGameplayStatics::GetWorldDeltaSeconds(this);
		if (LastShotTime >= ShotInterval)
		{
			FireAtPlayer();
			bPlayedSound = false;
			LastShotTime = 0.f;
		}
		if (LastShotTime >= ShotInterval - SoundOffset && !bPlayedSound)
		{
			bPlayedSound = true;
			PlayFireSound();
		}
	}
	
	

	LookAtPlayer();
}

void ASharpShooterEnemy::BeginPlay() {
	Super::BeginPlay();



}



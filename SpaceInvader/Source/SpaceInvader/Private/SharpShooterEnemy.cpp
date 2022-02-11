

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
}


void ASharpShooterEnemy::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	

	MoveLogic();
	FiringLogic();

	LookAtPlayer();
}

void ASharpShooterEnemy::BeginPlay() {
	Super::BeginPlay();



}

void ASharpShooterEnemy::MoveLogic()
{
	if (PlayerPawn == nullptr)
		return;

	if (!IsInInnerRange())
	{
		FVector ToPlayerVector = PlayerPawn->GetActorLocation() - GetActorLocation();
		ToPlayerVector.Z = 0.f;

		Move(ToPlayerVector);
	}
	else if (IsInInnerRange()) {
		FVector ToPlayerVector = PlayerPawn->GetActorLocation() - GetActorLocation();
		ToPlayerVector.Z = 0.f;

		Move(-ToPlayerVector);
	}

}

void ASharpShooterEnemy::FiringLogic()
{
	if (PlayerPawn == nullptr)
		return;
	LastShotTime += UGameplayStatics::GetWorldDeltaSeconds(this);
	if (ShotInterval <= LastShotTime)
	{
		
		FireAtPlayer();
		LastShotTime = 0.f;
	}

}

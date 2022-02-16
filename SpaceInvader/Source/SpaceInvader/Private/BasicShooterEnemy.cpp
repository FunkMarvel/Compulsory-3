

#include "BasicShooterEnemy.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"

ABasicShooterEnemy::ABasicShooterEnemy() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpinnerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpinnerMesh"));
	SpinnerMesh->SetupAttachment(Mesh);

	ProjectileForwardOffset = 40.f;
	ShotInterval = 0.7f;
	MovmentSpeed = 200.f;
	InnerRange = 500.f;
	FireRange = 3000.f;
	ProjectileSpeed = 700.f;
	StartHealth = 5.f;
	currentTilt = 20.f;
}


void ABasicShooterEnemy::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	
	FVector Direction = FVector::ZeroVector;

	Direction = GetToPlayerDirection();

	if (!IsInInnerRange())
	{
		Move(Direction.GetSafeNormal());
	} 

	//firing logic
	if (IsInFireRange())
	{
		if (PlayerPawn != nullptr) {
			LastShotTime += UGameplayStatics::GetWorldDeltaSeconds(this);
			if (ShotInterval <= LastShotTime)
			{
				FireAtPlayer();
				LastShotTime = 0.f;
				PlayFireSound();
			}
		}
	}
	
		
	//rotating
	RotateMeshAfterMovment(Mesh, GetToPlayerDirection().GetSafeNormal());

	// Spinning Spinner so that the Spinner Spins
	SpinSpinner(SpinnerSpinSpeed);

	

	LookAtPlayer();
}

void ABasicShooterEnemy::BeginPlay() {
	Super::BeginPlay();

	
	
}

void ABasicShooterEnemy::SpinSpinner(float SpinSpeed)
{
	SpinnerMesh->AddLocalRotation(FRotator(0.f, 0.f, SpinSpeed));
}




#include "HulkBossEnemy.h"
#include "Components/StaticMeshComponent.h"
#include "Curves/CurveFloat.h"

AHulkBossEnemy::AHulkBossEnemy() {
	
	/*for (int32 i = 0; i < 4; i++)
	{
		SpinnerMeshes[i] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH %d"), i);
	}*/
	Spinner1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PinnerOne"));
	CURVETEST = CreateDefaultSubobject<UCurveFloat>(TEXT("CURVE"));
}

void AHulkBossEnemy::BeginPlay()
{
	Super::BeginPlay();
}

void AHulkBossEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector ShootVector = GetToPlayerDirection().GetSafeNormal();

	StartOfShotTime += DeltaTime;
	ShootVector = ShootVector.RotateAngleAxis(CURVETEST->GetFloatValue(StartOfShotTime * 0.1f) * 90.f, GetActorUpVector());
	FireInDirection(ShootVector);

}

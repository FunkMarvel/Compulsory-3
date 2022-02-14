

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
}

void AHulkBossEnemy::Tick(float DeltaTime)
{

}



#include "HulkBossEnemy.h"
#include "Components/StaticMeshComponent.h"
#include "Curves/CurveFloat.h"
#include "Kismet/GameplayStatics.h"


AHulkBossEnemy::AHulkBossEnemy() {
	
	/*for (int32 i = 0; i < 4; i++)
	{
		SpinnerMeshes[i] = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH %d"), i);
	}*/
	Spinner1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PinnerOne"));
	CURVETEST = CreateDefaultSubobject<UCurveFloat>(TEXT("CURVE"));
}

void AHulkBossEnemy::NormalState()
{
	if (!bEnterState)
	{
		bEnterState = true;
		// On Enter State Logic
	}
	//moving and so on
}

void AHulkBossEnemy::ClosingBeamState()
{
	if (!bEnterState)
	{
		bEnterState = true;
		// On Enter State Logic
		Direction = GetToPlayerDirection().GetSafeNormal();
	}

	

	StartOfShotTime += UGameplayStatics::GetWorldDeltaSeconds(this);
	FVector OffSetVec = Direction.RotateAngleAxis(CURVETEST->GetFloatValue(StartOfShotTime * 0.5f) * 90.f, GetActorUpVector());
	FireInDirection(OffSetVec);
}

void AHulkBossEnemy::ChangeCurrentState(HulkState NewState)
{
	currentState = NewState;

	bEnterState = false;
}

void AHulkBossEnemy::BeginPlay()
{
	Super::BeginPlay();
	ChangeCurrentState(HulkState::ClosingBeam);
}

void AHulkBossEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	switch (currentState)
	{
	case AHulkBossEnemy::Normal:
		NormalState();
		break;
	case AHulkBossEnemy::ClosingBeam:
		ClosingBeamState();
		break;
	
	}
	

}

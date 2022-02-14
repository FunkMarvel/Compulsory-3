

#include "HulkBossEnemy.h"
#include "Components/StaticMeshComponent.h"
#include "Curves/CurveFloat.h"
#include "Kismet/GameplayStatics.h"


AHulkBossEnemy::AHulkBossEnemy() {
	ProjectileSpeed = 3000.f;
	ShotInterval = 0.05f;
	ClosingBeamDuration = 1.f;
	ProjectileForwardOffset = 200.f;

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
		StartOfStateTime = 0.f;
	}

	StartOfStateTime += UGameplayStatics::GetWorldDeltaSeconds(this);;
	LastShotTime += UGameplayStatics::GetWorldDeltaSeconds(this);
	if (LastShotTime >= ShotInterval)
	{
		FVector OffSetVecR = Direction.RotateAngleAxis(CURVETEST->GetFloatValue(StartOfStateTime * (1/ClosingBeamDuration)) * 90.f, GetActorUpVector());
		FVector OffSetVecL = Direction.RotateAngleAxis(-CURVETEST->GetFloatValue(StartOfStateTime * (1 / ClosingBeamDuration)) * 90.f, GetActorUpVector());
		FireInDirection(OffSetVecR);
		FireInDirection(OffSetVecL);
		LastShotTime = 0.f;

		
	}
	//is the beam finished?
	if (StartOfStateTime * (1 / ClosingBeamDuration) >= 1.f)
	{
		ChangeCurrentState(HulkState::Normal);
	}
	
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

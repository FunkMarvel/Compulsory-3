

#include "HulkBossEnemy.h"
#include "Components/StaticMeshComponent.h"
#include "Curves/CurveFloat.h"
#include "Kismet/GameplayStatics.h"


AHulkBossEnemy::AHulkBossEnemy() {
	ProjectileSpeed = 3000.f;
	ShotInterval = 0.05f;

	ClosingBeamDuration = 1.f;
	ClosingBeamCooldown = 2.f;

	RotatingBeamDuration = 5.f;
	RotatingBeamCooldown = 2.f;

	ProjectileForwardOffset = 0.f;
	InnerRange = 1000.f;

	Spinner1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PinnerOne"));

	ClosingBeamCurve = CreateDefaultSubobject<UCurveFloat>(TEXT("ClosingBeamCurve"));
	RotatingBeamCurve = CreateDefaultSubobject<UCurveFloat>(TEXT("RotatingBeamCurve"));

	currentTilt = 40.f;
}

void AHulkBossEnemy::NormalState()
{
	if (!bEnterState)
	{
		bEnterState = true;
		StartOfStateTime = 0.f;
		// On Enter State Logic
		NextBeamIndex = FMath::RandRange(0, 1);
	}
	StartOfStateTime += UGameplayStatics::GetWorldDeltaSeconds(this);

	FVector Direction = GetToPlayerDirection().GetSafeNormal();
	Move(Direction);
	RotateMeshAfterMovment(Mesh, Direction);

	

	switch (NextBeamIndex)
	{
	case 0:
		if (IsInInnerRange() && StartOfStateTime >= ClosingBeamCooldown)
		{
			ChangeCurrentState(HulkState::ClosingBeam);
		}
		break;
	case 1:
		if (IsInInnerRange() && StartOfStateTime >= RotatingBeamCooldown)
		{
			ChangeCurrentState(HulkState::RotatingBeam);
		}
		break;
	}

	

}

void AHulkBossEnemy::ClosingBeamState()
{
	if (!bEnterState)
	{
		bEnterState = true;
		// On Enter State Logic
		ClosingBeamDirection = GetToPlayerDirection().GetSafeNormal();
		StartOfStateTime = 0.f;
		LastShotTime = 0.f;
	}

	StartOfStateTime += UGameplayStatics::GetWorldDeltaSeconds(this);
	LastShotTime += UGameplayStatics::GetWorldDeltaSeconds(this);
	if (LastShotTime >= ShotInterval)
	{
		FVector OffSetVecR = ClosingBeamDirection.RotateAngleAxis(ClosingBeamCurve->GetFloatValue(StartOfStateTime * (1/ClosingBeamDuration)) * 90.f, GetActorUpVector());
		FVector OffSetVecL = ClosingBeamDirection.RotateAngleAxis(-ClosingBeamCurve->GetFloatValue(StartOfStateTime * (1 / ClosingBeamDuration)) * 90.f, GetActorUpVector());
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

void AHulkBossEnemy::RotateBeamState()
{
	if (!bEnterState)
	{
		bEnterState = true;
		StartOfStateTime = 0.f;
		LastShotTime = 0.f;
		ClosingBeamDirection = GetToPlayerDirection().GetSafeNormal();
		// On Enter State Logic
	}
	
	StartOfStateTime += UGameplayStatics::GetWorldDeltaSeconds(this);
	LastShotTime += UGameplayStatics::GetWorldDeltaSeconds(this);

	if (LastShotTime >= ShotInterval){

		LastShotTime = 0.f;
		FVector OffSetVecR = ClosingBeamDirection.RotateAngleAxis(RotatingBeamCurve->GetFloatValue(StartOfStateTime * (1 / RotatingBeamDuration)) * 90.f, GetActorUpVector());
		UE_LOG(LogTemp, Warning, TEXT("CURRENT: %f"), RotatingBeamCurve->GetFloatValue(StartOfStateTime * (1 / RotatingBeamDuration)) * 90.f)
			UE_LOG(LogTemp, Warning, TEXT("CURRENT: %s"), *OffSetVecR.ToString())
		FireInDirection(OffSetVecR);
		FireInDirection(-OffSetVecR);

	}
	//is the beam finished?
	if (StartOfStateTime * (1 / RotatingBeamDuration) >= 1.f)
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
	ChangeCurrentState(HulkState::Normal);
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
	case AHulkBossEnemy::RotatingBeam:
		RotateBeamState();
		break;
	
	}
	

}

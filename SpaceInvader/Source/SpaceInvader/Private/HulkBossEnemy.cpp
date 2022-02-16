

#include "HulkBossEnemy.h"
#include "Components/StaticMeshComponent.h"
#include "Curves/CurveFloat.h"
#include "Kismet/GameplayStatics.h"


AHulkBossEnemy::AHulkBossEnemy() {
	AttackingScale = 1.4f;

	ProjectileSpeed = 3000.f;
	ShotInterval = 0.04f;

	ClosingBeamDuration = 1.f;
	ClosingBeamCooldown = 2.f;

	RotatingBeamDuration = 5.f;
	RotatingBeamCooldown = 2.f;

	ProjectileForwardOffset = 0.f;
	InnerRange = 3000.f;

	SpinnerOne   = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpinenrOne"));
	SpinnerOne->SetupAttachment(GetRootComponent());
	SpinnerTwo   = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpinenrTwo"));
	SpinnerTwo->SetupAttachment(GetRootComponent());
	SpinnerThree = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpinenrThree"));
	SpinnerThree->SetupAttachment(GetRootComponent());
	

	ClosingBeamCurve = CreateDefaultSubobject<UCurveFloat>(TEXT("ClosingBeamCurve"));
	RotatingBeamCurve = CreateDefaultSubobject<UCurveFloat>(TEXT("RotatingBeamCurve"));

	currentTilt = 40.f;
}

void AHulkBossEnemy::SpinBlades(float Speed)
{
	float DeltaSpeed = Speed * UGameplayStatics::GetWorldDeltaSeconds(this);
	
	SpinnerOne->AddLocalRotation(FRotator(0.f, DeltaSpeed,0.f));
	SpinnerTwo->AddLocalRotation(FRotator(0.f, -DeltaSpeed * 1.1f, 0.f));
	SpinnerThree->AddLocalRotation(FRotator(0.f, DeltaSpeed * 1.2f, 0.f));
	

}

void AHulkBossEnemy::ScaleSpinner(UStaticMeshComponent* MeshComp, const float Scale, const float Alpha)
{
	SpinnerThree->SetWorldScale3D(FMath::Lerp(MeshComp->GetComponentScale(), FVector(Scale),
		UGameplayStatics::GetWorldDeltaSeconds(this) * Alpha));
	return;
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

	ScaleSpinner(SpinnerThree, 1.f, 5.f);

	StartOfStateTime += UGameplayStatics::GetWorldDeltaSeconds(this);
	FVector Direction = GetToPlayerDirection().GetSafeNormal();
	Move(Direction);
	RotateMeshAfterMovment(Mesh, Direction);

	SpinBlades(SpinnerBaseSpeed);


	switch (NextBeamIndex)
	{
	case 0:
		if (IsInInnerRange() && StartOfStateTime >= ClosingBeamCooldown)
		{
			ChangeCurrentState(HulkState::ClosingBeam);
			PlayFireSound();
		}
		break;
	case 1:
		if (IsInInnerRange() && StartOfStateTime >= RotatingBeamCooldown)
		{
			ChangeCurrentState(HulkState::RotatingBeam);
			PlayFireSound();
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
		StartSoundTime = 0.f;
	}

	

	ScaleSpinner(SpinnerThree, AttackingScale, 10.f);

	StartOfStateTime += UGameplayStatics::GetWorldDeltaSeconds(this);
	LastShotTime += UGameplayStatics::GetWorldDeltaSeconds(this);
	StartSoundTime += UGameplayStatics::GetWorldDeltaSeconds(this);
	SpinBlades(SpinnerAttackModifier);

	if (LastShotTime >= ShotInterval)
	{
		FVector OffSetVecR = ClosingBeamDirection.RotateAngleAxis(ClosingBeamCurve->GetFloatValue(StartOfStateTime * (1/ClosingBeamDuration)) * 90.f, GetActorUpVector());
		FVector OffSetVecL = ClosingBeamDirection.RotateAngleAxis(-ClosingBeamCurve->GetFloatValue(StartOfStateTime * (1 / ClosingBeamDuration)) * 90.f, GetActorUpVector());
		FireInDirection(OffSetVecR);
		FireInDirection(OffSetVecL);
		LastShotTime = 0.f;

		
	}

	//repeat audio
	if (StartSoundTime >= FiringSound->GetDuration())
	{
		PlayFireSound();
		StartSoundTime = 0.f;
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
		StartSoundTime = 0.f;
		ClosingBeamDirection = GetToPlayerDirection().GetSafeNormal();
		// On Enter State Logic
	}
	
	ScaleSpinner(SpinnerThree, AttackingScale, 10.f);

	StartOfStateTime += UGameplayStatics::GetWorldDeltaSeconds(this);
	LastShotTime += UGameplayStatics::GetWorldDeltaSeconds(this);
	StartSoundTime += UGameplayStatics::GetWorldDeltaSeconds(this);
	SpinBlades(SpinnerAttackModifier);


	if (LastShotTime >= ShotInterval){

		LastShotTime = 0.f;
		FVector OffSetVecR = ClosingBeamDirection.RotateAngleAxis(RotatingBeamCurve->GetFloatValue(StartOfStateTime * (1 / RotatingBeamDuration)) * 90.f, GetActorUpVector());
		UE_LOG(LogTemp, Warning, TEXT("CURRENT: %f"), RotatingBeamCurve->GetFloatValue(StartOfStateTime * (1 / RotatingBeamDuration)) * 90.f)
			UE_LOG(LogTemp, Warning, TEXT("CURRENT: %s"), *OffSetVecR.ToString())
		FireInDirection(OffSetVecR);
		FireInDirection(-OffSetVecR);

	}

	//repeat audio
	if (StartSoundTime >= FiringSound->GetDuration())
	{
		PlayFireSound();
		StartSoundTime = 0.f;
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

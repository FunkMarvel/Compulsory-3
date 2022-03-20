#include "FinalBossEnemy.h"

#include "GameHUD.h"
#include "Components/ActorComponent.h"
#include "LaserBeamComponent.h"
#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Math/UnrealMathUtility.h"
#include "SpaceInvader/SpaceInvaderGameModeBase.h"

AFinalBossEnemy::AFinalBossEnemy()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// setting up side comps:
	LeftSideCapsuleComp = CreateDefaultSubobject<UCapsuleComponent>("LeftSideCapsuleComponent");
	LeftSideCapsuleComp->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	LeftSideCapsuleComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	LeftSideCapsuleComp->SetupAttachment(GetRootComponent());
	LeftSideCapsuleComp->SetRelativeLocation(GetActorRightVector() * EBossPart::Left * WingOffset);

	RightSideCapsuleComp = CreateDefaultSubobject<UCapsuleComponent>("RightSideCapsuleComponent");
	RightSideCapsuleComp->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	RightSideCapsuleComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	RightSideCapsuleComp->SetupAttachment(GetRootComponent());
	RightSideCapsuleComp->SetRelativeLocation(GetActorRightVector() * EBossPart::Right * WingOffset);

	// setting up side mesh:
	LeftSideMesh = CreateDefaultSubobject<UStaticMeshComponent>("LeftSideMesh");
	LeftSideMesh->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	LeftSideMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LeftSideMesh->SetupAttachment(LeftSideCapsuleComp);
	// LeftSideMesh->SetRelativeLocation(GetActorRightVector() * EBossPart::Left * WingOffset);

	RightSideMesh = CreateDefaultSubobject<UStaticMeshComponent>("RightSideMesh");
	RightSideMesh->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	RightSideMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RightSideMesh->SetupAttachment(RightSideCapsuleComp);
	// RightSideMesh->SetRelativeLocation(GetActorRightVector() * EBossPart::Right * WingOffset);

	// combat components
	LeftLaserBeamParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("LeftLaserParticles"));
	LeftLaserBeamParticle->SetupAttachment(GetRootComponent());

	RightLaserBeamParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("RightLaserParticles"));
	RightLaserBeamParticle->SetupAttachment(GetRootComponent());
	
	LeftLaserBeamComp = CreateDefaultSubobject<ULaserBeamComponent>(TEXT("LeftLaserBeam"));
	// LeftLaserBeamComp->ParticleSystemComponent = LeftLaserBeamParticle;
	// LeftLaserBeamComp->ApplyWorldOffset(GetActorLocation() + GetActorRightVector() * EBossPart::Left * WingOffset, false);

	RightLaserBeamComp = CreateDefaultSubobject<ULaserBeamComponent>(TEXT("RightLaserBeam"));
	// RightLaserBeamComp->ParticleSystemComponent = RightLaserBeamParticle;
	// // RightLaserBeamComp->ApplyWorldOffset(GetActorLocation() + GetActorRightVector() * EBossPart::Right * WingOffset, false);


	// audio
	FiringSound = CreateDefaultSubobject<USoundBase>(TEXT("Fire Sound"));

	// Setting basic variables
	StartHealth = 60;
	MovmentSpeed = 2000.f;
	FireRange = 200.f;
	InnerRange = 3500.f;
	ShotInterval = 0.25f;
	ProjectileForwardOffset = 500.f;
	ProjectileSpeed = 3500.f;

	DamageCollide = 4.f;

	LastShotTime = ShotInterval;

	// Material
	ChangeColorDuration = 0.4f;
}

void AFinalBossEnemy::BeginPlay()
{
	Super::BeginPlay();

	PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	SetActorRotation(GetToPlayerDirection().Rotation());

	LeftLaserBeamComp->ParticleSystemComponent = LeftLaserBeamParticle;
	RightLaserBeamComp->ParticleSystemComponent = RightLaserBeamParticle;
	SetBeamsOn(false);

	
}

void AFinalBossEnemy::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	switch (CurrentState)
	{
	case EBossState::Normal:
		NormalState();
		break;
	case EBossState::DirectFire:
		DirectFireState();
		break;
	case EBossState::ClosingBeam:
		ClosingBeamState();
		break;
	case EBossState::RotatingBeam:
		RotateBeamState();
		break;
	case EBossState::SecondPhase:
		SecondPhaseState();
		break;
	}

	if (bLateUpdate == true)
	{
		// handle UI
		AGameHUD* HUD = Cast<AGameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
		if (HUD != nullptr)
		{
			HUD->GetBossHealthBar()->ShowHealthBarBPEvent();
			HUD->GetBossHealthBar()->SetOwnerOfBar(this);
		}
		bLateUpdate = false;
	}
}

void AFinalBossEnemy::NormalState()
{
	if (IsInInnerRange())
	{
		ChangeCurrentState(EBossState::DirectFire);
	}
	else
	{
		FVector Direction{GetToPlayerDirection()};
		RotateBossPart(EBossPart::Middle, GetToPlayerDirection().Rotation());
		Move(Direction);
	}
}

void AFinalBossEnemy::DirectFireState()
{
	if (FVector::DotProduct(GetLeftDirToPlayer(), GetRightDirToPlayer()) > 0.4f)
	{
		RotateBossPart(EBossPart::Middle, GetToPlayerDirection().Rotation());
	}
	
	RotateBossPart(EBossPart::Left, GetLeftDirToPlayer().Rotation());
	RotateBossPart(EBossPart::Right, GetRightDirToPlayer().Rotation());

	if (!IsInFireRange() && LastShotTime >= ShotInterval && bFireFromLeft)
	{
		FireFromPart(EBossPart::Left);
		bFireFromLeft = !bFireFromLeft;
		LastShotTime = 0.f;
	}
	else if (!IsInFireRange() && LastShotTime >= ShotInterval)
	{
		FireFromPart(EBossPart::Right);
		bFireFromLeft = !bFireFromLeft;
		LastShotTime = 0.f;
	}
	else if (!IsInFireRange())
	{
		LastShotTime += GetWorld()->GetDeltaSeconds();
	}
	if (!IsInInnerRange()) ChangeCurrentState(EBossState::Normal);
	if (AttackTimer >= TimeToChangeAttack && !bRotateBeams)
	{
		AttackTimer = -0.1;
		ChangeCurrentState(EBossState::ClosingBeam);
		return;
	}
	else if (AttackTimer >= TimeToChangeAttack)
	{
		AttackTimer = -0.1;
		ChangeCurrentState(EBossState::RotatingBeam);
		return;
	}
	AttackTimer += GetWorld()->GetDeltaSeconds();
}

void AFinalBossEnemy::ClosingBeamState()
{
	LeftStartDirection = GetActorRightVector()*EBossPart::Left;
	RightStartDirection = GetActorRightVector()*EBossPart::Right;

	if (AttackTimer <= 0)
	{
		// UE_LOG(LogTemp, Warning, TEXT("Set Directions."));
		CloseBeamTimer = -0.1;
		SetBeamsOn(true);
		FinalBeamDirection = GetToPlayerDirection();
		LeftLaserBeamComp->SetEmitterDirection(LeftStartDirection);
		RightLaserBeamComp->SetEmitterDirection(RightStartDirection);
	}

	if (AttackTimer > 0 && CloseBeamTimer <= TimeToCloseBeams)
	{
		// UE_LOG(LogTemp, Warning, TEXT("Beam timer %f"), CloseBeamTimer);
		CloseBeamTimer += GetWorld()->GetDeltaSeconds();
		float Alpha = CloseBeamTimer/TimeToCloseBeams;
		Alpha = FMath::Clamp<float>(Alpha, 0, 1);
		FVector LeftCurrentDirection{FMath::Lerp(LeftStartDirection, FinalBeamDirection, Alpha)};
		FVector RightCurrentDirection{FMath::Lerp(RightStartDirection, FinalBeamDirection, Alpha)};

		LeftLaserBeamComp->SetEmitterDirection(LeftCurrentDirection);
		RightLaserBeamComp->SetEmitterDirection(RightCurrentDirection);
		
	} else if (AttackTimer >= TimeToChangeAttack || CloseBeamTimer >= TimeToCloseBeams)
	{
		if (bCanRotateBeams) bRotateBeams = true;
		
		SetBeamsOn(false);
		AttackTimer = 0;
		ChangeCurrentState(EBossState::DirectFire);
	}
	else
	{
		CloseBeamTimer = 0;
	}
	AttackTimer += GetWorld()->GetDeltaSeconds();
}

void AFinalBossEnemy::RotateBeamState()
{
	if (AttackTimer <= 0)
	{
		SpinBeamTimer = 0;
		RightStartDirection = GetActorRightVector()*EBossPart::Right;
		SetBeamsOn(true);
		AttackTimer += GetWorld()->GetDeltaSeconds();
	}
	else if (AttackTimer <= TimeToChangeAttack && SpinBeamTimer <= TimeToSpinBeams)
	{
		float Theta{SpinBeamTimer*2*PI/TimeToSpinBeams};
		FVector NewDirection{FVector(RightStartDirection.X*cos(Theta) - RightStartDirection.Y*sin(Theta),
			RightStartDirection.X*sin(Theta) - RightStartDirection.Y*cos(Theta), 0.f)};

		LeftLaserBeamComp->SetEmitterDirection(NewDirection*EBossPart::Left);
		RightLaserBeamComp->SetEmitterDirection(NewDirection*EBossPart::Right);
		SpinBeamTimer += GetWorld()->GetDeltaSeconds();
	}
	else if (AttackTimer >= TimeToChangeAttack || SpinBeamTimer >= TimeToSpinBeams)
	{
		SetBeamsOn(false);
		AttackTimer = 0;
		bRotateBeams = false;
		ChangeCurrentState(EBossState::DirectFire);
	}
	AttackTimer += GetWorld()->GetDeltaSeconds();
}

void AFinalBossEnemy::SecondPhaseState()
{
	bRotateBeams = true;
	bCanRotateBeams = true;
	AttackTimer = 0;
	ChangeCurrentState(EBossState::DirectFire);
}

void AFinalBossEnemy::OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Health <= 0) SetBeamsOn(false);
	
	Super::OnHit(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	if (Health <= 0.5*StartHealth && !bCanRotateBeams)
	{
		ChangeCurrentState(EBossState::SecondPhase);
	}
	else if (Health <= 0.75*StartHealth && !bSpeedUpShot)
	{
		ShotInterval = 0.125f;
		bSpeedUpShot = true;
	}
}

void AFinalBossEnemy::RotateBossPart(EBossPart PartToRotate, FRotator NewRotation)
{
	FRotator CurrentRot{};
	FRotator InterpRot{};

	float DeltaTime = GetWorld()->GetDeltaSeconds();
	
	switch (PartToRotate)
	{
	case EBossPart::Left:
		CurrentRot = LeftSideMesh->GetComponentRotation();
		InterpRot = FMath::RInterpConstantTo(CurrentRot, NewRotation, DeltaTime, 100);
		LeftSideMesh->SetWorldRotation(InterpRot);
		break;

	case EBossPart::Middle:
		CurrentRot = GetActorRotation();
		InterpRot = FMath::RInterpConstantTo(CurrentRot, NewRotation, DeltaTime, 200);
		SetActorRotation(InterpRot);
		break;

	case EBossPart::Right:
		CurrentRot = RightSideMesh->GetComponentRotation();
		InterpRot = FMath::RInterpConstantTo(CurrentRot, NewRotation, DeltaTime, 100);
		RightSideMesh->SetWorldRotation(NewRotation);
		break;
	}
}

inline FVector AFinalBossEnemy::GetLeftDirToPlayer()
{
	FVector PlayerLoc{PlayerPawn->GetActorLocation()};
	return (PlayerLoc - LeftSideMesh->GetComponentLocation()).GetSafeNormal();
}

inline FVector AFinalBossEnemy::GetRightDirToPlayer()
{
	FVector PlayerLoc{PlayerPawn->GetActorLocation()};
	return (PlayerLoc - RightSideMesh->GetComponentLocation()).GetSafeNormal();
}

void AFinalBossEnemy::FireFromPart(EBossPart PartToFireFrom)
{
	if (ProjectileClass)
	{
		FVector Direction{};
		FVector Origin{};
		FRotator Rotation{};

		switch (PartToFireFrom)
		{
		case EBossPart::Left:
			Direction = GetLeftDirToPlayer();
			Origin = LeftSideMesh->GetComponentLocation();
			Rotation = LeftSideMesh->GetComponentRotation();
			break;
			
		case EBossPart::Middle:
			Direction = GetToPlayerDirection();
			Origin = GetActorLocation();
			Rotation = GetActorRotation();
			break;

		case EBossPart::Right:
			Direction = GetRightDirToPlayer();
			Origin = RightSideMesh->GetComponentLocation();
			Rotation = RightSideMesh->GetComponentRotation();
			break;
		}
		
		//the line under is unefficient, but since we dont have diffrent types of bullets we are using this
		ProjectileClass.GetDefaultObject()->ProjectileMovmentComponent->InitialSpeed = ProjectileSpeed;
		AProjectile* NewProjectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass,
			Origin + Direction * ProjectileForwardOffset,
			Rotation);
		/*GEngine->AddOnScreenDebugMessage(-10, 1, FColor::Green, "Sharpshooter!");*/
		if (NewProjectile)
			NewProjectile->SetOwner(this);
	}
}

void AFinalBossEnemy::SetBeamsOn(bool bBeamsOn)
{
	if (bBeamsOn)
	{
		LeftLaserBeamComp->SetBeamActive(true);
		RightLaserBeamComp->SetBeamActive(true);
		LeftLaserBeamComp->SetDamageActive();
		RightLaserBeamComp->SetDamageActive();
		
	} else if (!bBeamsOn) {
		LeftLaserBeamComp->SetBeamActive(false);
		RightLaserBeamComp->SetBeamActive(false);
		LeftLaserBeamComp->SetDamageInactive();
		RightLaserBeamComp->SetDamageInactive();
	}
}

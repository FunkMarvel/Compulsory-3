#include "FinalBossEnemy.h"

#include "LaserBeamComponent.h"
#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Particles/ParticleSystemComponent.h"

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
	LeftSideMesh->SetRelativeLocation(GetActorRightVector() * EBossPart::Left * WingOffset);

	RightSideMesh = CreateDefaultSubobject<UStaticMeshComponent>("RightSideMesh");
	RightSideMesh->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	RightSideMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RightSideMesh->SetupAttachment(RightSideCapsuleComp);
	RightSideMesh->SetRelativeLocation(GetActorRightVector() * EBossPart::Right * WingOffset);

	// combat components
	// LaserBeamParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("LaserParticles"));
	// LaserBeamParticle->SetupAttachment(GetRootComponent());
	//
	// LaserBeamComp = CreateDefaultSubobject<ULaserBeamComponent>(TEXT("LaserBeam"));
	// LaserBeamComp->ComponentRefrence.ComponentProperty = FName(TEXT("LaserBeamParticle"));


	// audio
	FiringSound = CreateDefaultSubobject<USoundBase>(TEXT("Fire Sound"));

	// Setting basic variables
	StartHealth = 7;
	MovmentSpeed = 500.f;
	FireRange = 200.f;
	InnerRange = 1000.f;
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
		// LookAtPlayer();
		Move(Direction);
		RotateMeshAfterMovment(Mesh, Direction);
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
}

void AFinalBossEnemy::ClosingBeamState()
{
}

void AFinalBossEnemy::RotateBeamState()
{
}

void AFinalBossEnemy::OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnHit(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	
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
		if (NewProjectile != nullptr)
			NewProjectile->SetOwner(this);
	}
}

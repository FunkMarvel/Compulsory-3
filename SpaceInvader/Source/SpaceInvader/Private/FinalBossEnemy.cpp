


#include "FinalBossEnemy.h"

#include "LaserBeamComponent.h"
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
	LeftSideCapsuleComp->SetRelativeLocation(-GetActorRightVector()*WingOffset);

	RightSideCapsuleComp = CreateDefaultSubobject<UCapsuleComponent>("RightSideCapsuleComponent");
	RightSideCapsuleComp->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	RightSideCapsuleComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	RightSideCapsuleComp->SetupAttachment(GetRootComponent());
	RightSideCapsuleComp->SetRelativeLocation(GetActorRightVector()*WingOffset);

	// setting up side mesh:
	LeftSideMesh = CreateDefaultSubobject<UStaticMeshComponent>("LeftSideMesh");
	LeftSideMesh->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	LeftSideMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LeftSideMesh->SetupAttachment(Mesh);
	LeftSideMesh->SetRelativeLocation(-GetActorRightVector()*WingOffset);

	RightSideMesh = CreateDefaultSubobject<UStaticMeshComponent>("RightSideMesh");
	RightSideMesh->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	RightSideMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RightSideMesh->SetupAttachment(Mesh);
	RightSideMesh->SetRelativeLocation(GetActorRightVector()*WingOffset);

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
	MovmentSpeed = 10000.f;
	FireRange = 4000.f;
	InnerRange = 1000.f;

	DamageCollide = 4.f;

	// Material
	ChangeColorDuration = 0.4f;
}

void AFinalBossEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void AFinalBossEnemy::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	switch (CurrentState)
	{
	case BossState::Normal:
		NormalState();
		break;
	case BossState::DirectFire:
		DirectFireState();
		break;
	case BossState::ClosingBeam:
		ClosingBeamState();
		break;
	case BossState::RotatingBeam:
		RotateBeamState();
		break;
	}
}

void AFinalBossEnemy::NormalState()
{

	if (IsInInnerRange())
	{
		ChangeCurrentState(BossState::DirectFire);
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
	
}

void AFinalBossEnemy::ClosingBeamState()
{
}

void AFinalBossEnemy::RotateBeamState()
{
}

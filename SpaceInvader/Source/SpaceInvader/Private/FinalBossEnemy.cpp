


#include "FinalBossEnemy.h"
#include "Components/CapsuleComponent.h"

AFinalBossEnemy::AFinalBossEnemy()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Health = StartHealth;
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>("CapsuleComponent");
	CapsuleComp->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	CapsuleComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SetRootComponent(CapsuleComp);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());

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


	// audio
	FiringSound = CreateDefaultSubobject<USoundBase>(TEXT("Fire Sound"));

	// Setting basic variables
	StartHealth = 7;
	MovmentSpeed = 200.f;
	FireRange = 4000.f;
	InnerRange = 1000.f;

	DamageCollide = 4.f;

	// Material
	ChangeColorDuration = 0.4f;
}

void AFinalBossEnemy::BeginPlay()
{
	Super::BeginPlay();
}

void AFinalBossEnemy::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

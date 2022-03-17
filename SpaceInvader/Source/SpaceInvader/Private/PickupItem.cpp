


#include "PickupItem.h"

#include "ShipPawn.h"
#include "Components/CapsuleComponent.h"
#include "SpaceInvader/SpaceInvaderGameModeBase.h"

// Sets default values
APickupItem::APickupItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));
	CapsuleComponent->SetCollisionObjectType(ECC_WorldDynamic);
	SetRootComponent(CapsuleComponent);

	CapsuleComponent->SetSimulatePhysics(false);
	CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CapsuleComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
	// CapsuleComponent->SetEnableGravity(false);

	CosmeticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cosmetic Mesh"));
	CosmeticMeshComponent->SetupAttachment(GetRootComponent());

	CosmeticMeshComponent->SetSimulatePhysics(false);
	CosmeticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

// Called when the game starts or when spawned
void APickupItem::BeginPlay()
{
	Super::BeginPlay();
	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &APickupItem::ApplyEffect);
}

// Called every frame
void APickupItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickupItem::ApplyEffect(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AShipPawn::StaticClass()))
	{
		ASpaceInvaderGameModeBase* GameMode{ Cast<ASpaceInvaderGameModeBase>(GetWorld()->GetAuthGameMode()) };
		if (GameMode)
		{
			GameMode->AddScore(ScoreValue);
		}
		
	}
}


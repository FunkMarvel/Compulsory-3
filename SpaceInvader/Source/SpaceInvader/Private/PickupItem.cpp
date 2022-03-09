


#include "PickupItem.h"

#include "Components/CapsuleComponent.h"

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
	
}

// Called every frame
void APickupItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickupItem::ApplyEffect()
{
}


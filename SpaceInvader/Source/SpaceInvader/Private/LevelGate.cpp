


#include "LevelGate.h"

#include "ShipPawn.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALevelGate::ALevelGate() : AActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collider"));
	Collider->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	SetRootComponent(Collider);
	Collider->SetSimulatePhysics(false);
	Collider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Collider->SetCollisionResponseToAllChannels(ECR_Overlap);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> GateMesh(TEXT("StaticMesh'/Game/Models/MaterialSphere.MaterialSphere'"));
	PortalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PortalMesh"));
	PortalMesh->SetStaticMesh(GateMesh.Object);
	PortalMesh->SetupAttachment(Collider);
	PortalMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	PortalMesh->SetSimulatePhysics(false);
	
	Levels.Add(TEXT("MainLevel"));
	Levels.Add(TEXT("NewLevel"));

}

// Called when the game starts or when spawned
void ALevelGate::BeginPlay()
{
	Super::BeginPlay();
	Collider->OnComponentBeginOverlap.AddUniqueDynamic(this, &ALevelGate::ChangeLevel);
}

void ALevelGate::ChangeLevel(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OtherActor->IsA<AShipPawn>())
	{
		int NextLevel{};
		FString CurrentMapName = GetWorld()->GetMapName();
		CurrentMapName.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);

		for (int i{}; i < Levels.Num(); i++)
		{
			if (CurrentMapName == Levels[i])
			{
				NextLevel = i + 1;
				break;
			}
		}

		if (NextLevel >= Levels.Num()) NextLevel = 0;

		UGameplayStatics::OpenLevel(GetWorld(), FName(*Levels[NextLevel]), false);
	}
}

// Called every frame
void ALevelGate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


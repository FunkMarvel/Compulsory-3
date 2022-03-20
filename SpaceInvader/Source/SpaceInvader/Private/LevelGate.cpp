


#include "LevelGate.h"

#include "MainGameInstance.h"
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
	
	PortalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PortalMesh"));
	PortalMesh->SetupAttachment(Collider);
	PortalMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	PortalMesh->SetSimulatePhysics(false);

	PortalSpinnerOne = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PortalSpinnerOne"));
	PortalSpinnerOne->SetupAttachment(Collider);
	PortalSpinnerOne->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	PortalSpillerTwo = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PortalSpinnerTwo"));
	PortalSpillerTwo->SetupAttachment(Collider);
	PortalSpillerTwo->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	
	Levels.Add(TEXT("MainLevel"));
	Levels.Add(TEXT("FinalBossLevel"));

}

// Called when the game starts or when spawned
void ALevelGate::BeginPlay()
{
	Super::BeginPlay();
	Collider->OnComponentBeginOverlap.AddUniqueDynamic(this, &ALevelGate::ChangeLevel);
}

void ALevelGate::SpinSpinners()
{
	float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);

	PortalMesh->AddRelativeRotation(FRotator(0.f, DeltaTime * PortalMeshSpinnerSpeed , 0.f));
	PortalSpinnerOne->AddRelativeRotation(FRotator(0.f, DeltaTime * PortalSpinnerOneSpeed , 0.f));
	PortalSpillerTwo->AddRelativeRotation(FRotator(0.f, DeltaTime * PortalSpinnerTwoSpeed , 0.f));
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

		//saves the players stats
		UGameInstance* GameInstance = GetGameInstance();
		if (GameInstance->IsA(UMainGameInstance::StaticClass()))
		{
			UMainGameInstance* MainGameInstance = Cast<UMainGameInstance>(GameInstance);
			AShipPawn* ShipPawn = Cast<AShipPawn>(OtherActor);
			
			MainGameInstance->SetPlayerStats(ShipPawn->Health, ShipPawn->Ammo, ShipPawn->Stamina,
				ShipPawn->StaminaTimer);
		}

		UGameplayStatics::OpenLevel(GetWorld(), FName(*Levels[NextLevel]), false);
	}
}

// Called every frame
void ALevelGate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SpinSpinners();
}







#include "HealthPickup.h"

#include "ShipPawn.h"

AHealthPickup::AHealthPickup() : APickupItem()
{
}

AHealthPickup::~AHealthPickup()
{
}

void AHealthPickup::ApplyEffect(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::ApplyEffect(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	if (!OtherActor) return;
	if (OtherActor->IsA<AShipPawn>())
	{
		AShipPawn* OtherShip = Cast<AShipPawn>(OtherActor);

		if ((OtherShip->MaxHealth - OtherShip->Health) < Healing)
		{
			OtherShip->Health += Healing;
		}
		else
		{
			OtherShip->Health = OtherShip->MaxHealth;
		}

		Destroy();
	}
}

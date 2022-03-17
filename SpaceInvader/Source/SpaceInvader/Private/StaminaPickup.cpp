


#include "StaminaPickup.h"

#include "ShipPawn.h"

AStaminaPickup::AStaminaPickup()
{
}

AStaminaPickup::~AStaminaPickup()
{
}

void AStaminaPickup::ApplyEffect(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::ApplyEffect(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	if (!OtherActor) return;
	if (OtherActor->IsA<AShipPawn>())
	{
		AShipPawn* OtherShip = Cast<AShipPawn>(OtherActor);

		if ((OtherShip->MaxStamina - OtherShip->Stamina) > StaminaRecharge)
		{
			OtherShip->Stamina += StaminaRecharge;
			OtherShip->StaminaTimer = 0;
		}
		else
		{
			OtherShip->Stamina = OtherShip->MaxStamina - 1;
			OtherShip->StaminaTimer = OtherShip->StaminaRechargeTime;
		}
		
		Destroy();
	}
	
}

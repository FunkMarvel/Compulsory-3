

#pragma once

#include "CoreMinimal.h"
#include "PickupItem.h"
#include "StaminaPickup.generated.h"

/**
 * 
 */
UCLASS()
class SPACEINVADER_API AStaminaPickup : public APickupItem
{
	GENERATED_BODY()

public:
	AStaminaPickup();
	~AStaminaPickup();

protected:
	UPROPERTY(EditDefaultsOnly, Category="Effect")
		int32 StaminaRecharge{1};

	virtual void ApplyEffect(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};



#pragma once

#include "CoreMinimal.h"
#include "PickupItem.h"
#include "HealthPickup.generated.h"

/**
 * 
 */
UCLASS()
class SPACEINVADER_API AHealthPickup : public APickupItem
{
	GENERATED_BODY()

public:
	AHealthPickup();
	~AHealthPickup();

protected:
	UPROPERTY(EditDefaultsOnly, Category="Effect")
		int32 Healing{10};
	
	virtual void ApplyEffect(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};

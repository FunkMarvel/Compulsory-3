

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LaserBeamComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACEINVADER_API ULaserBeamComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULaserBeamComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	
	UPROPERTY()
	bool bBeamActive = false;
	UPROPERTY(EditAnywhere, Category = "LaserBeam")
	FVector EmitterDirection = FVector::XAxisVector;
	
	FTimerHandle CoolDownTimerHandle;
	UPROPERTY()
	bool bDamage = true;
	void SetDamageActive(){bDamage =true; }
	void SetDamageInactive(){ bDamage = false; }
	
	void SetBeamActive(bool bActive);
	// void SetRelativeEmitterLocation(FVector StartPos);
	
	void SetEmitterDirection(FVector NewDirection);
	
	UPROPERTY()
	class UParticleSystemComponent* ParticleSystemComponent = nullptr;
	
private:
	UPROPERTY()
	FVector Target;
	
};

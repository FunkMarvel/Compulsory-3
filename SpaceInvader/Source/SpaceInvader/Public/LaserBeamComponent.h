

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
	
	//this needs to be the exact name of the ParticleSystemComponent you are going to refrence
	//see LaserBeamDemo for example
	UPROPERTY(EditAnywhere, Category = "Beam")
	FComponentReference ComponentRefrence;

	void SetTarget(FVector NewTarget){Target = NewTarget; }
	void SetBeamVisibility(bool bVisible);

	float time = 0.f;
	
private:
	UPROPERTY()
	FVector Target;
	
	UPROPERTY()
	class UParticleSystemComponent* ParticleSystemComponent = nullptr;
};

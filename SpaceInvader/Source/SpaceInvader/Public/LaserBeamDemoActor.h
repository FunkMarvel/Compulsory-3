

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LaserBeamDemoActor.generated.h"

UCLASS()
class SPACEINVADER_API ALaserBeamDemoActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALaserBeamDemoActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//my deseg ---------
	UPROPERTY(EditAnywhere, Category = "Main")
	class UParticleSystemComponent* ParticleSystemComponent= nullptr;
	UPROPERTY(EditAnywhere, Category = "Main")
	class ULaserBeamComponent* LaserBeamComponent = nullptr;
	float time = 0.f;
	
};

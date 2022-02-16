

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnParticleEffectActor.generated.h"

UCLASS()
class SPACEINVADER_API ASpawnParticleEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnParticleEffectActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//could have done this in a simpler way, using the tick function and if args, but i think this is the proper way to do it
	UPROPERTY(EditAnywhere, Category = "FX")
		class UParticleSystemComponent* ParticleToSpawn = nullptr;
	UPROPERTY(EditAnywhere, Category = "FX")
		float TimeToDestroy;
	FTimerHandle DestroyTimerHandle;

	//since the StartTimer needs a void func, and Destroy() returns a bool, i made a shell function that only calls Destroy()
	UFUNCTION()
		void DestroySheelFunc();
};

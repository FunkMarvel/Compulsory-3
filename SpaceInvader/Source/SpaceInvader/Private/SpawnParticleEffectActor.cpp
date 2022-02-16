

#include "Particles/ParticleSystemComponent.h"
#include "SpawnParticleEffectActor.h"

// Sets default values
ASpawnParticleEffectActor::ASpawnParticleEffectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ParticleToSpawn = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem"));
	SetRootComponent(ParticleToSpawn);
	ParticleToSpawn->bAutoActivate = true;
	TimeToDestroy = 5.f;

}

// Called when the game starts or when spawned
void ASpawnParticleEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(DestroyTimerHandle, this, &ASpawnParticleEffectActor::DestroySheelFunc, TimeToDestroy);
}

// Called every frame
void ASpawnParticleEffectActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



}

void ASpawnParticleEffectActor::DestroySheelFunc() {
	Destroy();
}


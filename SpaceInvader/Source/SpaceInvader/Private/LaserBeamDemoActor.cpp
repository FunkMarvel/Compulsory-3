


#include "LaserBeamDemoActor.h"

#include "LaserBeamComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ALaserBeamDemoActor::ALaserBeamDemoActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystemComponent"));

	LaserBeamComponent = CreateDefaultSubobject<ULaserBeamComponent>(TEXT("LaserBeamComponent"));
	LaserBeamComponent->ParticleSystemComponent = ParticleSystemComponent;
	
}

// Called when the game starts or when spawned
void ALaserBeamDemoActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALaserBeamDemoActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	time += DeltaTime;
	FVector vec = GetActorForwardVector();
	FVector NewDirection = FVector(cos(time), sin(time), 0.f);
	LaserBeamComponent->SetEmitterDirection(NewDirection);

}


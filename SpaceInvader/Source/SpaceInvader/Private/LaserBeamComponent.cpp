


#include "LaserBeamComponent.h"

#include "Particles/ParticleSystemComponent.h"

// Sets default values for this component's properties
ULaserBeamComponent::ULaserBeamComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	
}


// Called when the game starts
void ULaserBeamComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	//ParticleSystemComponent->SetVectorParameter(FName("TargetL"), NewTarget);

	UActorComponent* RefrenceComponent = ComponentRefrence.GetComponent(GetOwner());
	
	if (RefrenceComponent != nullptr)
	{
		if (RefrenceComponent->IsA(UParticleSystemComponent::StaticClass()))
		{
			ParticleSystemComponent = Cast<UParticleSystemComponent>(RefrenceComponent);
		}
	}
}


// Called every frame
void ULaserBeamComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//TODO TEMP REmove

	Target = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();

	time += DeltaTime;
	if (time > 4.f)
	{
		SetBeamVisibility(false);
	}
	if (time > 5.f)
	{
		SetBeamVisibility(true);
	}
	
	//TODO TEmp EndRemove
	

	if (ParticleSystemComponent != nullptr)
	{
		ParticleSystemComponent->SetBeamEndPoint(0,Target);
	}
	// ...
}

void ULaserBeamComponent::SetBeamVisibility(bool bVisible)
{
	if (ParticleSystemComponent != nullptr)
	{
		ParticleSystemComponent->SetVisibility(bVisible, false);
	}
}


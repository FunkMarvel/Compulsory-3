


#include "LaserBeamComponent.h"

#include "DrawDebugHelpers.h"
#include "ShipPawn.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "Kismet/KismetMathLibrary.h"
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
	SetBeamActive(true);
	
}


// Called every frame
void ULaserBeamComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
	if (!bBeamActive || ParticleSystemComponent == nullptr)
	{
		return;
	}
	
	// shooting ray logic
	FHitResult HitResult;
	
	FVector RayStartLocation = ParticleSystemComponent->GetComponentLocation();
	FVector RayEndLocation = EmitterDirection.GetSafeNormal() * 100000.f; // temp distance
	GetWorld()->LineTraceSingleByChannel(HitResult, RayStartLocation, RayEndLocation, ECollisionChannel::ECC_WorldDynamic);
	//DrawDebugLine(GetWorld(), RayStartLocation, RayEndLocation, FColor::Blue, true);
	if (HitResult.IsValidBlockingHit())
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit"))
		UE_LOG(LogTemp, Warning, TEXT("%s"), *HitResult.Actor->GetName())
		if (HitResult.Actor->IsA(AShipPawn::StaticClass()))
		{
			AShipPawn* Ship = Cast<AShipPawn>(HitResult.Actor);
			if (!Ship->GetDashState())
			{
				if (bDamage)
				{
					Ship->Health += -30;
					if (Ship->Health < 0)
					{
						Ship->OnPlayerDeath.Broadcast();
					}
					bDamage = false;
					GetWorld()->GetTimerManager().SetTimer(CoolDownTimerHandle, this, &ULaserBeamComponent::SetDamageActive,
						0.7f, false);
					
				}
				RayEndLocation = HitResult.Actor->GetActorLocation();
			}
		}
		
	}
	ParticleSystemComponent->SetBeamEndPoint(0,RayEndLocation);
		
	
}

void ULaserBeamComponent::SetBeamActive(bool bActive)
{
	if (ParticleSystemComponent)
	{
		ParticleSystemComponent->SetVisibility(bActive, false);
	}
	bBeamActive = bActive;
}

// void ULaserBeamComponent::SetRelativeEmitterLocation(FVector StartPos)
// {
// 	EmitterLocation = StartPos;
// }

void ULaserBeamComponent::SetEmitterDirection(FVector NewDirection)
{
	EmitterDirection = NewDirection;
}


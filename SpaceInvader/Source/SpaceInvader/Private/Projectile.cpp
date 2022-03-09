// Fill out your copyright notice in the Description page of Project Settings.



#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "EnemyProjectile.h"
#include "ShipPawn.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"


// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh;

	ProjectileMovmentComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movment Component"));
	ProjectileMovmentComponent->InitialSpeed = 1100.f;
	ProjectileMovmentComponent->MaxSpeed = 1500.f;
	ProjectileMovmentComponent->ProjectileGravityScale = 0.f;

	Trail = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle System Component"));
	Trail->SetupAttachment(GetRootComponent());
	Trail->bAutoActivate = true;

	//overlap
	ProjectileMesh->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	ProjectileMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	
	ProjectileMesh->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnHit);


}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TimeAlive += DeltaTime;

	if (MaxTimeAlive < TimeAlive)
	{
		Destroy();
	}

}



void AProjectile::OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AProjectile::StaticClass()) || OtherActor->IsA(AShipPawn::StaticClass()))
	{
		
	}
	else
	{
		Destroy();
		SpawnOnHitFX();
		
	}
}

void AProjectile::SpawnOnHitFX()
{
	if (ParticleSystemHit)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleSystemHit, GetActorLocation());
	}
}


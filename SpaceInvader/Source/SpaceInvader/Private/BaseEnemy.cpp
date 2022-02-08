


#include "BaseEnemy.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"

// Sets default values
ABaseEnemy::ABaseEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Health = StartHealth;
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>("CapsuleComponent");
	CapsuleComp->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	SetRootComponent(CapsuleComp);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());


	StartHealth = 50;
	MovmentSpeed = 200.f;

	

	
}

// Called when the game starts or when spawned
void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	CapsuleComp->OnComponentHit.AddDynamic(this, &ABaseEnemy::OnHit);
	Health = StartHealth;
	
}

// Called every frame
void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*Move(FVector::XAxisVector);*/
}

void ABaseEnemy::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	GEngine->AddOnScreenDebugMessage(-10, 1, FColor::Green, "HIT!");
	//Code todo Damage and push away
}

void ABaseEnemy::FireAtPlayer()
{
	if (ProjectileClass)
	{
		AProjectile* NewProjectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass,
			GetActorLocation() + FVector::ZAxisVector * 100.f,
			GetActorRotation());

		NewProjectile->SetOwner(this);
	}

	

}

void ABaseEnemy::Move(const FVector &Direction)
{
	/*APawn* PlayerActor = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	
	FVector ToPlayerVector = PlayerActor->GetActorLocation() - GetActorLocation();*/

	

	AddActorWorldOffset(Direction.GetSafeNormal() * MovmentSpeed * UGameplayStatics::GetWorldDeltaSeconds(GetWorld()), true);

}

void ABaseEnemy::LookAtPlayer()
{
	APawn* PlayerActor = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	
	FVector ToPlayerVector = PlayerActor->GetActorLocation() - GetActorLocation();

	FRotator rot = ToPlayerVector.Rotation();

	SetActorRotation(rot);
}



#include "BaseEnemy.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Projectile.h"
#include "DrawDebugHelpers.h"



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
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	CapsuleComp->OnComponentHit.AddDynamic(this, &ABaseEnemy::OnHit);
	Health = StartHealth;


	
}

// Called every frame
void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*Move(FVector::XAxisVector);*/
}

bool ABaseEnemy::IsInAgroRange()
{
	if (PlayerPawn == nullptr)
		return false;
	float Distance = (PlayerPawn->GetActorLocation() - GetActorLocation()).Size();
	if (Distance <= AggroRange)
	{
		return true;
	}
	return false;
}

bool ABaseEnemy::IsInInnerRange()
{
	if (PlayerPawn == nullptr)
		return false;
	float Distance = (PlayerPawn->GetActorLocation() - GetActorLocation()).Size();
	if (Distance <= InnerRange)
	{
		return true;
	}
	return false;
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
		//the line under is unefficient, but since we dont have diffrent types of bullets we are using this
		ProjectileClass.GetDefaultObject()->ProjectileMovmentComponent->InitialSpeed = ProjectileSpeed;
		AProjectile* NewProjectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass,
			GetActorLocation() + GetActorForwardVector() * ProjectileForwardOffset,
			GetActorRotation());
		/*GEngine->AddOnScreenDebugMessage(-10, 1, FColor::Green, "Sharpshooter!");*/
		NewProjectile->SetOwner(this);
		DrawDebugSphere(GetWorld(), GetActorLocation() + GetActorForwardVector() * ProjectileForwardOffset, 40, 16, FColor::Red, false, 1.f);
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


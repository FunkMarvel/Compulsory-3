
#include "BaseEnemy.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Projectile.h"
#include "DrawDebugHelpers.h"
#include "EnemyProjectile.h"

#include "ShipPawn.h"


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


	StartHealth = 7;
	MovmentSpeed = 200.f;
	
	

	
}

// Called when the game starts or when spawned
void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	
	/*CapsuleComp->OnComponentBeginOverlap.AddDynamic(this, )*/
	CapsuleComp->OnComponentBeginOverlap.AddDynamic(this, &ABaseEnemy::OnHit);
	Health = StartHealth;


	
}

// Called every frame
void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*Move(FVector::XAxisVector);*/
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

void ABaseEnemy::RotateMeshAfterMovment(UStaticMeshComponent* Comp, FVector Direction)
{
	
	FVector v1 = GetActorUpVector();
	//rotates the (up) vector towards the target
	// 
	// gets the "right vector" compared to the player (enemies arent nececeraly rotated towards the player
	v1 = v1.RotateAngleAxis(-currentTilt, FVector::CrossProduct(Direction, GetActorUpVector()).GetSafeNormal() ); 
	/*DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + v1.GetSafeNormal() * 400.f, FColor::Blue, false,
		0.5f);*/
	
	FRotator r2 = UKismetMathLibrary::MakeRotFromZX(v1, GetActorForwardVector());
	
	
	/*DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + r2.Vector() * 400.f, FColor::Blue, false,
		0.5f);*/

	Comp->SetWorldRotation(FMath::RInterpTo(Comp->GetComponentRotation(), r2, UGameplayStatics::GetWorldDeltaSeconds(this),
		5.f));
	
}

void ABaseEnemy::OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	
	//Code todo Damage and push away
	if (OtherActor->IsA<AProjectile>())
	{
		if (!OtherActor->IsA<AEnemyProjectile>())
		{
			
			Health -= Cast<AProjectile>(OtherActor)->Damage;

			if (Health <= 0.f)
			{
				Destroy();
			}
		}
	}
	else if (OtherActor->IsA<AShipPawn>())
	{
		//ligic Here
	}

}

void ABaseEnemy::FireAtPlayer()
{
	if (ProjectileClass)
	{
		FVector Direction = (UGameplayStatics::GetPlayerPawn(this, 0)->GetActorLocation() - GetActorLocation());
		Direction.Normalize();

		//the line under is unefficient, but since we dont have diffrent types of bullets we are using this
		ProjectileClass.GetDefaultObject()->ProjectileMovmentComponent->InitialSpeed = ProjectileSpeed;
		AProjectile* NewProjectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass,
			GetActorLocation() + GetActorForwardVector() * ProjectileForwardOffset,
			Direction.Rotation());
		/*GEngine->AddOnScreenDebugMessage(-10, 1, FColor::Green, "Sharpshooter!");*/
		if (NewProjectile != nullptr)
			NewProjectile->SetOwner(this);
		
		
		DrawDebugSphere(GetWorld(), GetActorLocation() + GetActorForwardVector() * ProjectileForwardOffset, 40, 16, FColor::Red, false, 1.f);
	}

	

}

void ABaseEnemy::FireInDirection(FVector Direction)
{
	
	if (ProjectileClass)
	{
		Direction.Normalize();

		//the line under is unefficient, but since we dont have diffrent types of bullets we are using this
		ProjectileClass.GetDefaultObject()->ProjectileMovmentComponent->InitialSpeed = ProjectileSpeed;
		AProjectile* NewProjectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass,
			GetActorLocation() + GetToPlayerDirection().GetSafeNormal() * ProjectileForwardOffset,
			Direction.Rotation());
		/*GEngine->AddOnScreenDebugMessage(-10, 1, FColor::Green, "Sharpshooter!");*/
		if (NewProjectile != nullptr)
			NewProjectile->SetOwner(this);
	
		
		DrawDebugSphere(GetWorld(), GetActorLocation() + GetActorForwardVector() * ProjectileForwardOffset, 40, 16, FColor::Red, false, 1.f);
	}
}

void ABaseEnemy::Move(FVector Direction)
{
	/*APawn* PlayerActor = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	
	FVector ToPlayerVector = PlayerActor->GetActorLocation() - GetActorLocation();*/
	Direction.Normalize();
	


	AddActorWorldOffset(Direction * MovmentSpeed * UGameplayStatics::GetWorldDeltaSeconds(GetWorld()), true);

}

void ABaseEnemy::LookAtPlayer()
{
	APawn* PlayerActor = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	
	FVector ToPlayerVector = PlayerActor->GetActorLocation() - GetActorLocation();

	FRotator rot = FMath::RInterpTo(GetActorRotation(), ToPlayerVector.Rotation(),
		UGameplayStatics::GetWorldDeltaSeconds(this), 5.f);



	SetActorRotation(rot);
}


FVector ABaseEnemy::GetToPlayerDirection()
{
	return (PlayerPawn->GetActorLocation() - GetActorLocation()).GetSafeNormal();

}


	


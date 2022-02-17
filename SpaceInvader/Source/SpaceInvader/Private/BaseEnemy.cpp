
#include "BaseEnemy.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Projectile.h"
#include "DrawDebugHelpers.h"
#include "EnemyProjectile.h"
#include "Particles/ParticleSystemComponent.h"
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

	// audio
	FiringSound = CreateDefaultSubobject<USoundBase>(TEXT("Fire Sound"));

	// Setting basic variables
	StartHealth = 7;
	MovmentSpeed = 200.f;
	FireRange = 4000.f;
	InnerRange = 1000.f;

	DamageCollide = 4.f;

	// Material
	ChangeColorDuration = 0.4f;
	
}

// Called when the game starts or when spawned
void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	
	/*CapsuleComp->OnComponentBeginOverlap.AddDynamic(this, )*/
	CapsuleComp->OnComponentBeginOverlap.AddDynamic(this, &ABaseEnemy::OnHit);
	Health = StartHealth;

	//sets the start material to the material the enemy starts with
	StartMaterial = Mesh->GetMaterial(0)->GetMaterial();
	
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

bool ABaseEnemy::IsInFireRange()
{
	if (PlayerPawn == nullptr)
		return false;
	float Distance = (PlayerPawn->GetActorLocation() - GetActorLocation()).Size();
	if (Distance <= FireRange)
	{
		return true;
	}
	return false;
}

void ABaseEnemy::PlayFireSound()
{
	UGameplayStatics::PlaySound2D(GetWorld(), FiringSound);
}

void ABaseEnemy::HandleDestruction()
{
	OnEnemyDiedDelegate.Broadcast(EnemyIndex);
	PlayDeathFX();
	Destroy();
}

void ABaseEnemy::PlayDeathFX()
{
	if (FireParticleSystem)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FireParticleSystem, GetActorLocation());
	}
}

void ABaseEnemy::RotateMeshAfterMovment(UStaticMeshComponent* Comp, FVector Direction)
{
	FVector PsuedoRightVector = GetActorUpVector();	
	// gets the "right vector" compared to the player (enemies arent nececeraly rotated towards the player
	PsuedoRightVector = PsuedoRightVector.RotateAngleAxis(-currentTilt, FVector::CrossProduct(Direction, GetActorUpVector()).GetSafeNormal() ); 
	//creates the new rotation
	FRotator NewRotation = UKismetMathLibrary::MakeRotFromZX(PsuedoRightVector, GetActorForwardVector());
	//rotates the Mesh Component inputted accordingly
	Comp->SetWorldRotation(FMath::RInterpTo(Comp->GetComponentRotation(), NewRotation, 
		UGameplayStatics::GetWorldDeltaSeconds(this), 5.f));
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
				HandleDestruction();
				UE_LOG(LogTemp, Warning, TEXT("ON DEATH"));
				
			}
		}
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
		
		
		//DrawDebugSphere(GetWorld(), GetActorLocation() + GetActorForwardVector() * 
			//ProjectileForwardOffset, 40, 16, FColor::Red, false, 1.f);
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
	
		
		/*DrawDebugSphere(GetWorld(), GetActorLocation() + GetActorForwardVector() * 
			ProjectileForwardOffset, 40, 16, FColor::Red, false, 1.f);*/
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


	


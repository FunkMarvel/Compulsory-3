
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

void ABaseEnemy::OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	
	//Code todo Damage and push away
	if (OtherActor->IsA<AProjectile>())
	{
		GEngine->AddOnScreenDebugMessage(-1230, 1, FColor::Green, "BINGUS!");
		Health -= Cast<AProjectile>(OtherActor)->Damage;

		if (Health <= 0.f)
		{
			Destroy();
		}
	}

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
		//NewProjectile->SetOwner(this);
		DrawDebugSphere(GetWorld(), GetActorLocation() + GetActorForwardVector() * ProjectileForwardOffset, 40, 16, FColor::Red, false, 1.f);
	}

	

}

void ABaseEnemy::Move(FVector Direction)
{
	/*APawn* PlayerActor = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	
	FVector ToPlayerVector = PlayerActor->GetActorLocation() - GetActorLocation();*/
	Direction.Normalize();
	Direction += GetActorRightVector()*GetLeftRightMovment(Amplitude, Lambda);
	UE_LOG(LogTemp, Warning, TEXT("%f"), GetLeftRightMovment(4.f, 1.f));

	AddActorWorldOffset(Direction * MovmentSpeed * UGameplayStatics::GetWorldDeltaSeconds(GetWorld()), true);

}

void ABaseEnemy::LookAtPlayer()
{
	APawn* PlayerActor = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	
	FVector ToPlayerVector = PlayerActor->GetActorLocation() - GetActorLocation();

	FRotator rot = ToPlayerVector.Rotation();

	SetActorRotation(rot);
}

float ABaseEnemy::GetLeftRightMovment(const float &_Amplitude, const float &_Lambda)
{
	CurrentMovmentTime += UGameplayStatics::GetWorldDeltaSeconds(this);
	float f = FMath::Sin((1.f / Lambda) * CurrentMovmentTime) * Amplitude;
	return f;
}


	


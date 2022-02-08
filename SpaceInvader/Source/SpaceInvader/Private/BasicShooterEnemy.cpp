

#include "Kismet/GameplayStatics.h"
#include "BasicShooterEnemy.h"

ABasicShooterEnemy::ABasicShooterEnemy() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}


void ABasicShooterEnemy::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	UE_LOG(LogTemp, Warning, TEXT("TICK"));

	APawn* PlayerActor = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	
	FVector ToPlayerVector = PlayerActor->GetActorLocation() - GetActorLocation();
	ToPlayerVector.Z = 0.f;

	Move(ToPlayerVector);

	UE_LOG(LogTemp, Warning, TEXT("TICK"));

	LookAtPlayer();
}

void ABasicShooterEnemy::BeginPlay() {
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, 
		&ABasicShooterEnemy::FireAtPlayer, FireRate, true);
	
}
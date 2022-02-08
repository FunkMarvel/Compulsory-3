

#include "Kismet/GameplayStatics.h"
#include "BasicShooterEnemy.h"

void ABasicShooterEnemy::Tick(float DeltaTime) {
	APawn* PlayerActor = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	
	FVector ToPlayerVector = PlayerActor->GetActorLocation() - GetActorLocation();
	ToPlayerVector.Z = 0.f;

	Move(ToPlayerVector);

	LookAtPlayer();
}
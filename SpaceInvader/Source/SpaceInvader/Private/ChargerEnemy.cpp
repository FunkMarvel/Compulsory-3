


#include "ChargerEnemy.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"


AChargerEnemy::AChargerEnemy() {
	//compoennts
	BladesMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Blades Mesh"));
	BladesMesh->SetupAttachment(Mesh);

	MovmentSpeed = 200.f;
	InnerRange = 700.f;
	StartHealth = 50;
	ChargeSpeed = 600.f;
	currentState = ChargerState::Moving;

	//blades
	BladeNormalSpeed = 400.f;
	BladeWindupSpeed = 800.f;
	BladeChargeSpeed = 1400.f;
}

void AChargerEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveLogic();
	SpinBlades();

}

void AChargerEnemy::MoveLogic()
{
	if (PlayerPawn == nullptr)
		return;

	FVector ToPlayerVector = PlayerPawn->GetActorLocation() - GetActorLocation();
	ToPlayerVector.Z = 0.f;
	switch (currentState)
	{
	case AChargerEnemy::Moving:
		MovmentSpeed = NormalSpeed;
		Move(ToPlayerVector);
		break;
	case AChargerEnemy::WindUp:
		MovmentSpeed = WindupSpeed;
		Move(-ToPlayerVector);
		break;
	case AChargerEnemy::Charging:
		MovmentSpeed = ChargeSpeed;
		Move(ToPlayerVector);
		break;
	default:
		break;
	}

}

void AChargerEnemy::SpinBlades()
{
	float ToSpin = 0.f;
	switch (currentState)
	{
	case AChargerEnemy::Moving:
		ToSpin = BladeNormalSpeed;
		break;
	case AChargerEnemy::WindUp:
		ToSpin = BladeWindupSpeed;
		break;
	case AChargerEnemy::Charging:
		ToSpin = BladeChargeSpeed;
		break;
	default:
		break;
	}
	BladesMesh->AddLocalRotation(FRotator(0.f, ToSpin * UGameplayStatics::GetWorldDeltaSeconds(this), 0.f));
}



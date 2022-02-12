


#include "ChargerEnemy.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"


AChargerEnemy::AChargerEnemy() {
	//compoennts
	BladesMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Blades Mesh"));
	BladesMesh->SetupAttachment(Mesh);

	InnerRange = 700.f;
	StartHealth = 3;
	currentState = ChargerState::Moving;

	//WindUpTime = 1.f;
	MovmentSpeed = 200.f;
	NormalSpeed = 150.f;
	WindupSpeed = -200.f;
	ChargeSpeed = 600.f;


	//blades
	BladeNormalSpeed = 400.f;
	BladeWindupSpeed = 800.f;
	BladeChargeSpeed = 1400.f;
}

void AChargerEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentStateLogic();
	MoveLogic();
	SpinBlades();
	LookAtPlayer();

	switch (currentState)
	{
	case AChargerEnemy::Moving:
		TargetTilt = -20.f;
		break;
	case AChargerEnemy::WindUp:
		TargetTilt = 15.f;
		break;
	case AChargerEnemy::Charging:
		TargetTilt = -90.f;
		break;
	default:
		break;
	}


	float Angle = FMath::FInterpTo(Mesh->GetRelativeRotation().Pitch, TargetTilt, DeltaTime, 5.f);
	Mesh->SetRelativeRotation(FRotator(Angle, 0.f, 0.f));
}

void AChargerEnemy::CurrentStateLogic()
{
	if (IsInInnerRange())
	{
		currentState = ChargerState::WindUp;
		bFoundTarget = true;
	}


	if (bFoundTarget)
	{
		CurrentWindUpTime += UGameplayStatics::GetWorldDeltaSeconds(this);
		if (CurrentWindUpTime >= WindUpTime)
		{
			currentState = ChargerState::Charging;
		}
	}
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
		
		break;
	case AChargerEnemy::WindUp:
		MovmentSpeed = WindupSpeed;
		
		break;
	case AChargerEnemy::Charging:
		MovmentSpeed = ChargeSpeed;
		
		break;
	default:
		break;
	}
	Move(ToPlayerVector);

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



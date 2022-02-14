


#include "ChargerEnemy.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ShipPawn.h"


AChargerEnemy::AChargerEnemy() {
	//compoennts
	BladesMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Blades Mesh"));
	BladesMesh->SetupAttachment(Mesh);

	//Base variables
	InnerRange = 700.f;
	StartHealth = 3;
	currentState = ChargerState::Moving;

	//WindUp
	WindUpTime = 1.f;

	//Charge
	ChargeTime = 1.f;

	//Movment Speends
	MovmentSpeed = 200.f;
	NormalSpeed = 150.f;
	WindupSpeed = -200.f;
	ChargeSpeed = 90.f;


	//blade speeds
	BladeNormalSpeed = 400.f;
	BladeWindupSpeed = 800.f;
	BladeChargeSpeed = 1400.f;

	//tilt amounts
	NormalTilt = 30.f;
	WindUpTilt = 15.f;
	ChargeTilt = 75.f;
}

void AChargerEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (currentState)
	{
	case AChargerEnemy::Moving:
		MovingState();
		break;
	case AChargerEnemy::WindUp:
		WindUpState();
		break;
	case AChargerEnemy::Charging:
		ChargingState();
		break;
	case AChargerEnemy::CoolDown:
		CoolDownState();
		break;
	default:
		break;
	}

}



void AChargerEnemy::OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnHit(OverlappedComponent, OtherActor, OtherComp,
		OtherBodyIndex, bFromSweep, SweepResult);

	if (OtherActor->IsA<AShipPawn>())
	{
		currentState = ChargerState::CoolDown;

	}
	
}

void AChargerEnemy::MovingState()
{
	FVector Direction = GetToPlayerDirection().GetSafeNormal();
	MovmentSpeed = NormalSpeed;
	currentTilt = NormalTilt;
	RotateMeshAfterMovment(Mesh, Direction);
	Move(Direction);
	SpinBlades();


	if (IsInInnerRange())
	{
		currentState = ChargerState::WindUp;
		StateTime = 0.f;
	}
}

void AChargerEnemy::WindUpState()
{
	FVector Direction = -GetToPlayerDirection().GetSafeNormal();
	MovmentSpeed = WindupSpeed;
	currentTilt = WindUpTilt;
	RotateMeshAfterMovment(Mesh, Direction);
	Move(Direction);
	SpinBlades();

	StateTime += UGameplayStatics::GetWorldDeltaSeconds(this);

	if (StateTime >= WindUpTime)
	{
		currentState = ChargerState::Charging;
		StateTime = 0.f;
		
	}
}

void AChargerEnemy::ChargingState()
{
	FVector Direction = GetToPlayerDirection().GetSafeNormal();
	StateTime += UGameplayStatics::GetWorldDeltaSeconds(this);
}

void AChargerEnemy::CoolDownState()
{
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
	case AChargerEnemy::CoolDown:
		ToSpin = BladeNormalSpeed;
		break;
	default:
		break;
	}
	BladesMesh->AddLocalRotation(FRotator(0.f, ToSpin * UGameplayStatics::GetWorldDeltaSeconds(this), 0.f));
}



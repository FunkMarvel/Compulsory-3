// Fill out your copyright notice in the Description page of Project Settings.


#include "ShipPawn.h"
#include "GameFramework/PlayerController.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/PlayerInput.h"
#include "Components/InputComponent.h"
#include "BulletActor.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraActor.h"
#include "Engine/Engine.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Projectile.h"

static void InitializeDefaultPawnInputBinding() {
	static bool BindingsAdded{false};
	if (!BindingsAdded) {
		BindingsAdded = true;

		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("UpDown",EKeys::W,1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("UpDown",EKeys::S,-1.f));

		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("LeftRight",EKeys::D,1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("LeftRight",EKeys::A,-1.f));

		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("Aim", EKeys::Mouse2D, 1.f));

		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("Dash", EKeys::LeftShift));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("Focus", EKeys::SpaceBar));

		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("Shoot",EKeys::LeftMouseButton));
		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("Reload",EKeys::R));
	}
}

// Sets default values
AShipPawn::AShipPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("	StaticMesh'/Game/Models/PlaceHolderPlane/PlaceHolderPlane.PlaceHolderPlane'"));

	// collision and physics mesh:
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>("CapsuleComponent");
	CapsuleComp->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	SetRootComponent(CapsuleComp);

	// Rescale mass:
	FBodyInstance* BodyInstance = CapsuleComp->GetBodyInstance();
	BodyInstance->MassScale = 0.025;
	BodyInstance->LinearDamping = 0.f;
	BodyInstance->UpdateMassProperties();
	
	// enable physics and collision:
	CapsuleComp->SetSimulatePhysics(true);
	CapsuleComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CapsuleComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	CapsuleComp->SetEnableGravity(false);

	// set up cosmetic mesh:
	PlayerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Player Mesh"));
	PlayerMesh->SetStaticMesh(ShipMesh.Object);
	PlayerMesh->SetupAttachment(CapsuleComp);

	// Setting up camera:
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->bDoCollisionTest = false;
	SpringArm->SetUsingAbsoluteRotation(true);
	SpringArm->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));
	SpringArm->TargetArmLength = 2000.f;
	SpringArm->bEnableCameraLag = false;
	SpringArm->CameraLagSpeed = 5.f;

	SpringArm->SetupAttachment(CapsuleComp);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->bUsePawnControlRotation = false;
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
}

// Called when the game starts or when spawned
void AShipPawn::BeginPlay()
{
	Super::BeginPlay();
	InitLocation = PlayerMesh->GetComponentLocation();
}

// Called every frame
void AShipPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	InContact = false;

	// Handling movement:
	FVector Forward = GetActorForwardVector();
	FVector Sideways = GetActorRightVector();
	
	CapsuleComp->AddForce((Forward*XValue + Sideways*0.8*YValue)*Acceleration);

	// clamping max velocity:
	FVector currentVelocity = CapsuleComp->GetPhysicsLinearVelocity();
	FVector clampedVelocity = currentVelocity.GetClampedToMaxSize(SpeedLimit);
	CapsuleComp->SetPhysicsLinearVelocity(clampedVelocity);

	// animating cosmetic mesh:
	if (DashTimer < DashDuration) {
		PlayerMesh->SetRelativeRotation(FRotator(0,0,DashRotation/DashDuration * DashTimer));
	}
	else {
		FRotator CurrentRot = PlayerMesh->GetRelativeRotation();
		FRotator DestinationRot = FMath::RInterpConstantTo(CurrentRot, FRotator(0, 0, 45*YValue), DeltaTime, 100);
		PlayerMesh->SetRelativeRotation(DestinationRot);
	}
	DashTimer += DeltaTime;

	// handling sustained fire:
	if (bShooting && ShotTimer >= TimeBetweenShots) {
		Shoot();
		ShotTimer = 0;
	}
	else {
		ShotTimer += DeltaTime;
	}
}

// Called to bind functionality to input
void AShipPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent !=nullptr);
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InitializeDefaultPawnInputBinding();

	PlayerInputComponent->BindAxis("UpDown",this,&AShipPawn::MoveXAxis);
	PlayerInputComponent->BindAxis("LeftRight",this,&AShipPawn::MoveYAxis);
	
	PlayerInputComponent->BindAxis("Aim", this, &AShipPawn::Aim);

	PlayerInputComponent->BindAction("Dash",EInputEvent::IE_Pressed,this,&AShipPawn::Dash);
	PlayerInputComponent->BindAxis("Focus", this, &AShipPawn::Focus);
	//PlayerInputComponent->BindAction("Focus",EInputEvent::IE_Pressed,this,&AShipPawn::Focus);
	//PlayerInputComponent->BindAction("Focus",EInputEvent::IE_Released,this,&AShipPawn::Focus);

	PlayerInputComponent->BindAction("Shoot",EInputEvent::IE_Pressed,this,&AShipPawn::StartShooting);
	PlayerInputComponent->BindAction("Shoot",EInputEvent::IE_Released,this,&AShipPawn::EndShooting);

	PlayerInputComponent->BindAction("Reload",EInputEvent::IE_Pressed,this,&AShipPawn::Reload);

}

void AShipPawn::Reload() {
}

void AShipPawn::Shoot() {
	if (ProjectileClass)
	{
		FVector ShipVelocity = GetVelocity();
		FVector Forward = GetActorForwardVector();
		//the line under is unefficient, but since we dont have diffrent types of bullets we are using this
		ProjectileClass.GetDefaultObject()->ProjectileMovmentComponent->InitialSpeed = ProjectileSpeed;
		AProjectile* NewProjectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass,
			GetActorLocation() + Forward * ProjectileForwardOffset,
			GetActorRotation());
		GEngine->AddOnScreenDebugMessage(-10, 1, FColor::Green, "Sharpshooter!");
		NewProjectile->SetOwner(this);
	}
}

void AShipPawn::StartShooting() {
	bShooting = true;
	ShotTimer = TimeBetweenShots + 1;
}

void AShipPawn::EndShooting() {
	bShooting = false;
	ShotTimer = 0;
}

void AShipPawn::ResetLoaction() const {
}

void AShipPawn::MoveXAxis(float Value) {
	XValue = Value;
}

void AShipPawn::MoveYAxis(float Value) {
	YValue = Value;
}

void AShipPawn::Aim(float Value) {
	FVector MouseLocation;
	FVector MouseDirection;

	Cast<APlayerController>(GetController())->DeprojectMousePositionToWorld(MouseLocation, MouseDirection);
	MouseDirection.Z = 0.f;

	SetActorRotation(MouseDirection.Rotation());
	CapsuleComp->SetRelativeRotation(MouseDirection.Rotation());
}

void AShipPawn::Dash() {
	DashTimer = 0;

	FVector MouseLocation;
	FVector MouseDirection;
	FVector CurrentVelocity = GetVelocity();

	Cast<APlayerController>(GetController())->DeprojectMousePositionToWorld(MouseLocation, MouseDirection);
	MouseDirection.Z = 0.f;

	CapsuleComp->AddImpulse(MouseDirection * 2.5 *Acceleration);
	CapsuleComp->AddImpulse(-MouseDirection * Acceleration);
}

void AShipPawn::Focus(float Value) {

	FVector CurrentVelocity = -GetVelocity();
	CurrentVelocity.Normalize();
	CapsuleComp->AddForce(CurrentVelocity*0.7*Acceleration);
}


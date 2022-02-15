// Fill out your copyright notice in the Description page of Project Settings.


#include "ShipPawn.h"
#include "GameFramework/PlayerController.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
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
#include "DrawDebugHelpers.h"
#include "Components/WidgetComponent.h"
#include "HealthBarWidget.h"

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
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("StaticMesh'/Game/Models/PlayerPlane/Plane_2.Plane_2'"));

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
	CapsuleComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	CapsuleComp->SetEnableGravity(false);

	// set up cosmetic mesh:
	PlayerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Player Mesh"));
	PlayerMesh->SetStaticMesh(ShipMesh.Object);
	PlayerMesh->SetupAttachment(CapsuleComp);
	PlayerMesh->SetSimulatePhysics(false);
	PlayerMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Setting up camera:
	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	CameraArm->bDoCollisionTest = false;
	CameraArm->SetUsingAbsoluteRotation(true);
	CameraArm->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));
	CameraArm->TargetArmLength = 4000.f;
	CameraArm->bEnableCameraLag = false;
	CameraArm->CameraLagSpeed = 5.f;

	CameraArm->SetupAttachment(CapsuleComp);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->bUsePawnControlRotation = false;
	Camera->SetupAttachment(CameraArm, USpringArmComponent::SocketName);

	//// Setting up health bar:
	//HealthWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("Player Health Bar"));
	//HealthWidgetComp->SetupAttachment(CapsuleComp);
	//HealthWidgetComp->SetWidgetSpace(EWidgetSpace::Screen);
	//HealthWidgetComp->SetRelativeLocation(FVector(-200.f, 0.f, 0.f));
	
}

// Called when the game starts or when spawned
void AShipPawn::BeginPlay()
{
	Super::BeginPlay();
	InitLocation = PlayerMesh->GetComponentLocation();
	CapsuleComp->OnComponentBeginOverlap.AddDynamic(this, &AShipPawn::OnHit);

	//UHealthBarWidget* HealthBar = Cast<UHealthBarWidget>(HealthWidgetComp->GetUserWidgetObject());
	//HealthBar->SetOwnerOfBar(this);
}

// Called every frame
void AShipPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	InContact = false;

	// Handling movement:
	//FVector Forward = GetActorForwardVector();
	//FVector Sideways = GetActorRightVector();
	FVector AccelDirection = FVector(XValue, YValue, 0.f).GetSafeNormal();
	CapsuleComp->AddForce(AccelDirection*Acceleration);

	// clamping max velocity:
	FVector currentVelocity = CapsuleComp->GetPhysicsLinearVelocity();
	FVector clampedVelocity = currentVelocity.GetClampedToMaxSize(SpeedLimit);
	CapsuleComp->SetPhysicsLinearVelocity(clampedVelocity);
	
	// animating cosmetic mesh:
	if (DashTimer < DashDuration) {
		PlayerMesh->SetRelativeRotation(FRotator(0,0,DashRotation/DashDuration * DashTimer));
		DashTimer += DeltaTime;
	}
	else {
		FVector Velocity = GetVelocity().GetSafeNormal();
		FVector Sideways = GetActorRightVector();

		FRotator CurrentRot = PlayerMesh->GetRelativeRotation();
		FRotator DestinationRot = FMath::RInterpConstantTo(CurrentRot, FRotator(0, 0, 45*FVector::DotProduct(Velocity, Sideways)), DeltaTime, 100);
		PlayerMesh->SetRelativeRotation(DestinationRot);
		bDashing = false;
	}

	// handling sustained fire:
	if (bShooting && ShotTimer >= TimeBetweenShots) {
		Shoot();
		ShotTimer = 0;
	}
	else if (ShotTimer < TimeBetweenShots)  {
		ShotTimer += DeltaTime;
	}

	// handling stamina:
	if (Stamina < 3 && StaminaTimer < StaminaRechargeTime) {
		StaminaTimer += DeltaTime;
	}
	else if (Stamina < 3) {
		Stamina++;
		StaminaTimer = 0;
		if (DashRechargeSound) UGameplayStatics::PlaySound2D(GetWorld(), DashRechargeSound);
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

	PlayerInputComponent->BindAction("Shoot",EInputEvent::IE_Pressed,this,&AShipPawn::StartShooting);
	PlayerInputComponent->BindAction("Shoot",EInputEvent::IE_Released,this,&AShipPawn::EndShooting);

	PlayerInputComponent->BindAction("Reload",EInputEvent::IE_Pressed,this,&AShipPawn::Reload);

}

void AShipPawn::OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult) {
	
	if (OtherActor->IsA<AProjectile>() && OtherActor->GetOwner() != this && !bDashing) {
		GEngine->AddOnScreenDebugMessage(-10, 1, FColor::Red, "HIT!");
		AProjectile* Overlapper = Cast<AProjectile>(OtherActor);
		Health -= Overlapper->Damage;
		//UE_LOG(LogTemp, Warning, TEXT("Health: %f"), Health);
		if (Health <= 0) Death();
	}

}

void AShipPawn::Reload() {
	Ammo = MaxAmmo;
	if (ReloadingSound) UGameplayStatics::PlaySound2D(GetWorld(), ReloadingSound);
}

void AShipPawn::Shoot() {
	if (ProjectileClass && Ammo > 0)
	{
		FVector ShipVelocity = GetVelocity();
		FVector Forward = GetActorForwardVector();
		//the line under is unefficient, but since we dont have diffrent types of bullets we are using this
		ProjectileClass.GetDefaultObject()->ProjectileMovmentComponent->InitialSpeed = ProjectileSpeed;
		AProjectile* NewProjectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass,
			GetActorLocation() + Forward * ProjectileForwardOffset,
			GetActorRotation());

		GEngine->AddOnScreenDebugMessage(-10, 1, FColor::Green, "Shoot!");
		if (NewProjectile) NewProjectile->SetOwner(this);

		if (ShootingSound) UGameplayStatics::PlaySound2D(GetWorld(), ShootingSound);
		Ammo--;
	}
	else if (Ammo <= 0) {
		GEngine->AddOnScreenDebugMessage(-10, 1, FColor::Orange, "Out of Ammo!");
		if (AmmoWarning) UGameplayStatics::PlaySound2D(GetWorld(), AmmoWarning, 6.f);
	}
}

void AShipPawn::StartShooting() {
	bShooting = true;
}

void AShipPawn::EndShooting() {
	bShooting = false;
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
	if (StaminaTimer >= StaminaRechargeTime || Stamina > 0) {
		Stamina--;
		StaminaTimer = 0;
		DashTimer = 0;
		bDashing = true;
		if (DashSound) UGameplayStatics::PlaySound2D(GetWorld(), DashSound);

		FVector MouseLocation;
		FVector MouseDirection;
		FVector CurrentVelocity = GetVelocity();

		Cast<APlayerController>(GetController())->DeprojectMousePositionToWorld(MouseLocation, MouseDirection);
		MouseDirection.Z = 0.f;

		CapsuleComp->AddImpulse(MouseDirection * 2.5 *Acceleration);
		//CapsuleComp->AddImpulse(-MouseDirection * Acceleration);
	}
}

void AShipPawn::Focus(float Value) {

	FVector CurrentVelocity = -GetVelocity();
	CurrentVelocity.Normalize();
	CapsuleComp->AddForce(CurrentVelocity*0.7*Acceleration);
}

void AShipPawn::Death() {
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	DisableInput(PlayerController);
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	SetActorTickEnabled(false);
}
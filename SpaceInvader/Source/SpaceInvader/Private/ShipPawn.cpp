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

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>("CapsuleComponent");
	CapsuleComp->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	SetRootComponent(CapsuleComp);
	CapsuleComp->SetSimulatePhysics(true);
	CapsuleComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CapsuleComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	CapsuleComp->SetEnableGravity(false);

	PlayerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Player Mesh"));

	PlayerMesh->SetStaticMesh(ShipMesh.Object);
	PlayerMesh->SetupAttachment(CapsuleComp);

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

	FVector Forward = GetActorForwardVector();
	FVector Sideways = GetActorRightVector();
	
	CapsuleComp->AddForce((Forward*XValue + Sideways*YValue)*Acceleration);

	if ((bDashing && DashTimer < DashDuration) || DashTimer < DashDuration) {
		PlayerMesh->SetRelativeRotation(FRotator(0,0,DashRotation/DashDuration * DashTimer));
	}
	else {
		FRotator CurrentRot = PlayerMesh->GetRelativeRotation();
		FRotator DestinationRot = FMath::RInterpConstantTo(CurrentRot, FRotator(0, 0, 45*YValue), DeltaTime, 100);
		PlayerMesh->SetRelativeRotation(DestinationRot);
	}
	DashTimer += DeltaTime;
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
	PlayerInputComponent->BindAction("Dash",EInputEvent::IE_Released,this,&AShipPawn::EndDash);
	PlayerInputComponent->BindAxis("Focus", this, &AShipPawn::Focus);
	//PlayerInputComponent->BindAction("Focus",EInputEvent::IE_Pressed,this,&AShipPawn::Focus);
	//PlayerInputComponent->BindAction("Focus",EInputEvent::IE_Released,this,&AShipPawn::Focus);

	PlayerInputComponent->BindAction("Shoot",EInputEvent::IE_Pressed,this,&AShipPawn::Shoot);
	PlayerInputComponent->BindAction("Reload",EInputEvent::IE_Pressed,this,&AShipPawn::Reload);

}

void AShipPawn::Reload() {
}

void AShipPawn::Shoot() {
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
	bDashing = true;
	DashTimer = 0;

	FVector MouseLocation;
	FVector MouseDirection;
	FVector CurrentVelocity = GetVelocity();

	Cast<APlayerController>(GetController())->DeprojectMousePositionToWorld(MouseLocation, MouseDirection);
	MouseDirection.Z = 0.f;

	CapsuleComp->AddImpulse(MouseDirection * 2.5 *Acceleration);
	CapsuleComp->AddImpulse(-MouseDirection * Acceleration);
}

void AShipPawn::EndDash() {
	bDashing = false;
}

void AShipPawn::Focus(float Value) {
	
	//bFocused = !bFocused;
	
	//if (bFocused) {
	//	//Speed = FocusSpeedMod * BaseAcceleration;
	//}
	//else {
	//	//Speed = BaseAcceleration;
	//}

	//UE_LOG(LogTemp, Warning, TEXT("bFocused: %d"), bFocused);

	FVector CurrentVelocity = -GetVelocity();
	CurrentVelocity.Normalize();
	CapsuleComp->AddForce(CurrentVelocity*0.5*Acceleration);
}


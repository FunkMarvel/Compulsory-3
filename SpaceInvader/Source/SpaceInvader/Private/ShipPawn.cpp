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
#include "../SpaceInvaderGameModeBase.h"
#include "Components/WidgetComponent.h"
#include "HealthBarWidget.h"
#include "BaseEnemy.h"
#include "EnemyProjectile.h"

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
		
		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("Focus", EKeys::SpaceBar));

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

	// set up pointer mesh:
	PointerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pointer Mesh"));
	PointerMesh->SetupAttachment(CapsuleComp);
	PointerMesh->SetSimulatePhysics(false);
	PointerMesh->SetRelativeLocation(FVector(0.f,0.f,-200.f));
	PointerMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

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

	// Setting up Multishot Fire Arrows
	RightFireArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("RightFireArrowComponent"));
	RightFireArrowComponent->SetupAttachment(GetRootComponent());
	LeftFireArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("LeftFireArrowComponent"));
	LeftFireArrowComponent->SetupAttachment(GetRootComponent());

	//Setting up LeftRight TurretMeshes
	RightTurretSkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RightTurretSkeletalMeshComponent"));
	RightTurretSkeletalMeshComponent->SetupAttachment(PlayerMesh);
	RightTurretSkeletalMeshComponent->SetWorldScale3D(FVector(1.75));
	RightTurretSkeletalMeshComponent->SetRelativeLocation(FVector(-10, 70, 0));
	LeftTurretSkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LeftTurretSkeletalMeshComponent"));
	LeftTurretSkeletalMeshComponent->SetupAttachment(PlayerMesh);
	LeftTurretSkeletalMeshComponent->SetWorldScale3D(FVector(1.75));
	LeftTurretSkeletalMeshComponent->SetRelativeLocation(FVector(-10, -70, 0));
}

// Called when the game starts or when spawned
void AShipPawn::BeginPlay()
{
	Super::BeginPlay();
	InitLocation = PlayerMesh->GetComponentLocation();
	CapsuleComp->OnComponentBeginOverlap.AddDynamic(this, &AShipPawn::OnHit);
	Focus();
}

// Called every frame
void AShipPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Handling movement:
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
		FRotator DestinationRot = FMath::RInterpConstantTo(CurrentRot, FRotator(
			10.f * FVector::DotProduct(Velocity, GetActorForwardVector()),
			0,
			45*FVector::DotProduct(Velocity, Sideways)), DeltaTime, 100);
		PlayerMesh->SetRelativeRotation(DestinationRot);
		bDashing = false;
	}
	
	HandleShooting();

	// handling stamina:
	if (Stamina < MaxStamina && StaminaTimer < StaminaRechargeTime) {
		StaminaTimer += DeltaTime;
	}
	else if (Stamina < MaxStamina) {
		Stamina++;
		StaminaTimer = 0;
		if (DashRechargeSound) UGameplayStatics::PlaySound2D(GetWorld(), DashRechargeSound);
	}

	// handling pointer mesh rotation
	PointPointerMesh();
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
	PlayerInputComponent->BindAction("Focus",EInputEvent::IE_Released, this, &AShipPawn::Focus);

	PlayerInputComponent->BindAction("Shoot",EInputEvent::IE_Pressed,this,&AShipPawn::StartShooting);
	PlayerInputComponent->BindAction("Shoot",EInputEvent::IE_Released,this,&AShipPawn::EndShooting);

	//PlayerInputComponent->BindAction("Reload",EInputEvent::IE_Pressed,this,&AShipPawn::StartReload);
}

void AShipPawn::OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult) {
	
	if (OtherActor->IsA<AEnemyProjectile>() && OtherActor->GetOwner() != this && !bDashing) {
		GEngine->AddOnScreenDebugMessage(-10, 1, FColor::Red, "HIT!");
		AEnemyProjectile* Overlapper = Cast<AEnemyProjectile>(OtherActor);
		Health -= Overlapper->Damage;
		if (Health <= 0) OnPlayerDeath.Broadcast();
	}
	else if (OtherActor->IsA<ABaseEnemy>()) {
		GEngine->AddOnScreenDebugMessage(-10, 1, FColor::Red, "HIT!");
		ABaseEnemy* Overlapper = Cast<ABaseEnemy>(OtherActor);
		Health -= Overlapper->DamageCollide;

		if (Health <= 0) OnPlayerDeath.Broadcast();
	}
	else if (OtherActor->IsA<ABlockingVolume>()) { // Bounce back if pawn hits level bounds.
		FVector Back = -GetVelocity().GetSafeNormal();
		CapsuleComp->AddImpulse(Back*Acceleration);
	}

}

void AShipPawn::HandleShooting()
{
	//handling fire states
	float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	LastShotTimer += DeltaTime;

	if (LastShotTimer > StartReloadingTime && Ammo < MaxAmmo)
	{
		if (!bReloadFirstFrame)
		{
			bReloadFirstFrame = true;
			StartReload();
		}
		
		
		ReloadTime += DeltaTime;
		while (ReloadTime > ReloadTimePeriod)
		{
			ReloadTime += -ReloadTimePeriod;
			Ammo++;
		}
		
	}
	
	if (ECurrentFireState == EPlayerFireState::Normal)
	{
		
		// handling sustained NormalFire:
		if (bShooting && ShotTimer >= TimeBetweenShots) {
			ProjectileSpeed = NormalShootProjectileSpeed;
			Shoot();
			ShotTimer = 0;
			LastShotTimer = 0.f;
			bReloadFirstFrame = false;
		}
		else if (ShotTimer < TimeBetweenShots)  {
			ShotTimer += DeltaTime;
		}
	}
	else
	{
		// handling sustained MultiFire:
		if (bShooting && ShotTimer >= TimeBetweenShots) {
			ProjectileSpeed = MultiShootProjectileSpeed;
			Shoot();
			Shoot(RightFireArrowComponent->GetComponentLocation(), MultiShotAngle);
			Shoot(LeftFireArrowComponent->GetComponentLocation(), -MultiShotAngle);
			ShotTimer = 0;
			LastShotTimer = 0.f;
			bReloadFirstFrame = false;
		}
		else if (ShotTimer < TimeBetweenShots)  {
			ShotTimer += DeltaTime;
		}
	}
}

void AShipPawn::StartReload() {
	//Ammo = MaxAmmo;
	if (ReloadingSound) UGameplayStatics::PlaySound2D(GetWorld(), ReloadingSound);
}

void AShipPawn::Shoot() {
	if (ProjectileClass && Ammo > 0)
	{
		FVector ShipVelocity = GetVelocity();
		FVector Forward = GetActorForwardVector();
		//the line under is inefficient, but since we dont have diffrent types of bullets we are using this
		ProjectileClass.GetDefaultObject()->ProjectileMovmentComponent->InitialSpeed = ProjectileSpeed;
		AProjectile* NewProjectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass,
			GetActorLocation() + Forward * ProjectileForwardOffset,
			GetActorRotation());

		if (NewProjectile) NewProjectile->SetOwner(this);

		if (ShootingSound) UGameplayStatics::PlaySound2D(GetWorld(), ShootingSound);
		Ammo--;
	}
	else if (Ammo <= 0) {
		GEngine->AddOnScreenDebugMessage(-10, 1, FColor::Orange, "Out of Ammo!");
		if (AmmoWarning) UGameplayStatics::PlaySound2D(GetWorld(), AmmoWarning, 6.f);
	}
}

void AShipPawn::Shoot(FVector FireLocation, float Angle)
{
	if (ProjectileClass && Ammo > 0)
	{
		FVector ShipVelocity = GetVelocity();
		FVector Forward = GetActorForwardVector();
		//the line under is inefficient, but since we dont have diffrent types of bullets we are using this
		ProjectileClass.GetDefaultObject()->ProjectileMovmentComponent->InitialSpeed = ProjectileSpeed;
		AProjectile* NewProjectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass,
			FireLocation,
			GetActorRotation() + FRotator(0.f,Angle,0.f));

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

void AShipPawn::SetCurrentFireState(EPlayerFireState NewFireState)
{
	ECurrentFireState = NewFireState;

	switch (NewFireState)
	{
	case EPlayerFireState::Normal:
		if (RetractTurretAnimationAsset != nullptr)
		{
			RightTurretSkeletalMeshComponent->PlayAnimation(RetractTurretAnimationAsset, false);
			LeftTurretSkeletalMeshComponent->PlayAnimation(RetractTurretAnimationAsset, false);
		}
		break;
	case EPlayerFireState::Multi:
		if (DeployTurretAnimationAsset != nullptr)
		{
			RightTurretSkeletalMeshComponent->PlayAnimation(DeployTurretAnimationAsset, false);
			LeftTurretSkeletalMeshComponent->PlayAnimation(DeployTurretAnimationAsset, false);
		}
		break;
	}
	
}

void AShipPawn::PointPointerMesh()
{
	//gets the game mode
	AGameModeBase* GameModeBase = GetWorld()->GetAuthGameMode();
	if (GameModeBase->IsA<ASpaceInvaderGameModeBase>())
	{
		// casts the game mode
		ASpaceInvaderGameModeBase* SpaceGameMode = Cast<ASpaceInvaderGameModeBase>(GameModeBase);
		TArray<ABaseEnemy*> EnemyArray = SpaceGameMode->GetAllEnemies();

		//  Guard clause
		if (EnemyArray.Num() == 0)
		{
			return;
		}

		//UE_LOG(LogTemp, Warning, TEXT("Number of enemies - %d"), EnemyArray.Num())

		float MinDistance = 1000000000.f;
		int MinIndex = 0;

		// Finds the closest player
		for (int i = 0; i < EnemyArray.Num(); i++)
		{
			if (EnemyArray[i] != nullptr) {
				float Distance = (GetActorLocation() - EnemyArray[i]->GetActorLocation()).SizeSquared();
				if (Distance <= MinDistance)
				{
					MinDistance = Distance;
					MinIndex = i;
				}
			}
			
		}

		if (EnemyArray[MinIndex])
		{
			// creates a new rotation based on lerp and sets it
			CurrentPointerVec = FMath::VInterpTo(CurrentPointerVec,
				(GetActorLocation() - EnemyArray[MinIndex]->GetActorLocation()).GetSafeNormal(),
				UGameplayStatics::GetWorldDeltaSeconds(this), 10.f);
			PointerMesh->SetWorldRotation(CurrentPointerVec.Rotation());
		}
	}
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
		
	}
}

void AShipPawn::Focus() {
	//UE_LOG(LogTemp, Warning, TEXT("FOCUS!"))
	bFocus = !bFocus;
	if (bFocus)
	{
		SetCurrentFireState(EPlayerFireState::Multi);
	}
	else
	{
		SetCurrentFireState(EPlayerFireState::Normal);
	}
	
}
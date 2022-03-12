


#include "GameHUD.h"
#include "HealthBarWidget.h"
#include "DashBars.h"
#include "ShipPawn.h"
#include "AmmoBars.h"
#include "GameOverWidget.h"
#include "Kismet/GameplayStatics.h"

AGameHUD::AGameHUD() {
}

void AGameHUD::DrawHUD() {
	Super::DrawHUD();
}

void AGameHUD::BeginPlay() {
	Super::BeginPlay();
	UGameViewportClient* Viewport = GetWorld()->GetGameViewport();

	ViewSize = Viewport->Viewport->GetSizeXY();

	if (HealthBarClass) {
		
		HealthBar = CreateWidget<UHealthBarWidget>(GetWorld(), HealthBarClass);
		
		if (HealthBar) {
			HealthBar->SetOwnerOfBar(GetWorld()->GetFirstPlayerController()->GetPawn());
			HealthBar->AddToViewport();
			HealthBar->SetPositionInViewport(FVector2D(ViewSize.X*0.45f,ViewSize.Y*0.90f));
		}
	}

	if (BossHealthBarClass){
		BossHealthBar = CreateWidget<UHealthBarWidget>(GetWorld(), BossHealthBarClass);

		if (BossHealthBar)
		{
			//BossHealthBar->SetOwnerOfBar(GetWorld()->GetFirstPlayerController()->GetPawn());
			BossHealthBar->AddToViewport();
			//BossHealthBar->SetPositionInViewport(FVector2D(ViewSize.X * 0.1f, ViewSize.Y * 0.1f));
			BossHealthBar->SetVisibility(ESlateVisibility::Hidden);
			
		}
	}

	if (DashBarsClass) {

		DashBars = CreateWidget<UDashBars>(GetWorld(), DashBarsClass);

		if (DashBars) {
			DashBars->AddToViewport();
			DashBars->SetPositionInViewport(FVector2D(ViewSize.X*0.05f,ViewSize.Y*0.8f));
			for (int32 i = 0; i < 3; i++) {
				DashBars->UpdateStaminaBars(i, 1.f, 1.f);
			}
		}
	}

	if (AmmoBarsClass) {

		AmmoBars = CreateWidget<UAmmoBars>(GetWorld(), AmmoBarsClass);

		if (AmmoBars) {
			AmmoBars->AddToViewport();
			AmmoBars->SetPositionInViewport(FVector2D(ViewSize.X*0.825f,ViewSize.Y*0.8f));
			for (int32 i = 1; i <= 3; i++) {
				AmmoBars->UpdateAmmoBars(i, i);
			}
		}
	}

	if (GameOverClass) {

		GameOver = CreateWidget<UGameOverWidget>(GetWorld(), GameOverClass);

		if (GameOver) {
			GameOver->SetVisibility(ESlateVisibility::Hidden);
			GameOver->AddToViewport();
			GameOver->AddOnPress();
			GameOver->SetPositionInViewport(FVector2D(ViewSize.X*0.25f,ViewSize.Y*0.45f));
		}
	}

	if (GameWinClass) {

		GameWin = CreateWidget<UGameOverWidget>(GetWorld(), GameWinClass);

		if (GameWin) {
			GameWin->SetVisibility(ESlateVisibility::Hidden);
			GameWin->AddToViewport();
			GameWin->AddOnPress();
			GameWin->SetPositionInViewport(FVector2D(ViewSize.X*0.25f,ViewSize.Y*0.45f));
		}
	}
}

void AGameHUD::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	UpdateDashBars();
	UpdateAmmoBars();
}

void AGameHUD::UpdateDashBars() {
	APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	AShipPawn* PlayerShip{nullptr};

	if (PlayerPawn) {
		PlayerShip = Cast<AShipPawn>(PlayerPawn);

		DashBars->UpdateStaminaBars(PlayerShip->Stamina, PlayerShip->StaminaRechargeTime, PlayerShip->StaminaTimer);
	}
}

void AGameHUD::UpdateAmmoBars() {
	APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	AShipPawn* PlayerShip{nullptr};

	if (PlayerPawn) {
		PlayerShip = Cast<AShipPawn>(PlayerPawn);

		AmmoBars->UpdateAmmoBars(PlayerShip->Ammo, PlayerShip->MaxAmmo);
	}
}

void AGameHUD::ViewGameOver(bool ShowGameOver) {
	if (GameOver && ShowGameOver) { GameOver->SetVisibility(ESlateVisibility::Visible); }
	else if (GameOver) { GameOver->SetVisibility(ESlateVisibility::Hidden); }
}

void AGameHUD::ViewGameWin(bool ShowGameWin) {
	if (GameWin && ShowGameWin) { GameWin->SetVisibility(ESlateVisibility::Visible); }
	else if (GameWin) { GameWin->SetVisibility(ESlateVisibility::Hidden); }
}

UHealthBarWidget* AGameHUD::GetBossHealthBar()
{
	return BossHealthBar;
}

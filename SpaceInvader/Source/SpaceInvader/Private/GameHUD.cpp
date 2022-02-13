


#include "GameHUD.h"
#include "Kismet/GameplayStatics.h"

AGameHUD::AGameHUD() {

}

void AGameHUD::DrawHUD() {
	Super::DrawHUD();
}

void AGameHUD::BeginPlay() {
	Super::BeginPlay();

	if (HealthBarClass) {
		UGameViewportClient* Viewport = GetWorld()->GetGameViewport();

		ViewSize = Viewport->Viewport->GetSizeXY();
		
		HealthBar = CreateWidget<UHealthBarWidget>(GetWorld(), HealthBarClass);
		
		if (HealthBar) {
			HealthBar->SetOwnerOfBar(GetWorld()->GetFirstPlayerController()->GetPawn());
			HealthBar->AddToViewport();
			HealthBar->SetPositionInViewport(FVector2D(ViewSize.X*0.5f-200*0.5f,ViewSize.Y*0.95f));
		}
	}
}

void AGameHUD::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

//void AGameHUD::UpdateHealthBar(float percent) {
//	if (HealthBar) {
//		
//	}
//}

void AGameHUD::UpdateDashBars(float percent) {
}

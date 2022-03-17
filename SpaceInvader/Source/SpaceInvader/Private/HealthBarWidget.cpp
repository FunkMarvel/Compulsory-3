


#include "HealthBarWidget.h"
#include "Components/ProgressBar.h"
#include "ShipPawn.h"
#include "Engine.h"
#include "HulkBossEnemy.h"


UHealthBarWidget::UHealthBarWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {

}

void UHealthBarWidget::NativeConstruct() {
	Super::NativeConstruct();
}

void UHealthBarWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime) {

	Super::NativeTick(MyGeometry, InDeltaTime);
	
	if (!OwnerActor.IsValid()) return;

	AActor* Owner = Cast<AActor>(OwnerActor);

	if (Owner->IsA<AShipPawn>()) {  // updating for ship class.
		AShipPawn* OwnerShip = Cast<AShipPawn>(OwnerActor);
		HealthBar->SetPercent(OwnerShip->Health/OwnerShip->MaxHealth);
	}
	else if (Owner->IsA<AHulkBossEnemy>()){
		AHulkBossEnemy* HulkBossEnemy = Cast<AHulkBossEnemy>(OwnerActor);
		HealthBar->SetPercent(HulkBossEnemy->GetHealthPercent());
	}
	
}




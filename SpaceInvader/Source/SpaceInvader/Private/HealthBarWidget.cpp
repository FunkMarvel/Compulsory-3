


#include "HealthBarWidget.h"
#include "Components/ProgressBar.h"
#include "ShipPawn.h"
#include "BaseEnemy.h"

void UHealthBarWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime) {

	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!OwnerActor.IsValid()) return;

	AActor* Owner = Cast<AActor>(OwnerActor);

	if (Owner->IsA<AShipPawn>()) {
		AShipPawn* OwnerShip = Cast<AShipPawn>(OwnerActor);
		HealthBar->SetPercent(OwnerShip->Health/OwnerShip->MaxHealth);
	}
	//else if (Owner->IsA<ABaseEnemy>()) {
	//	ABaseEnemy* OwnerEnemy = Cast<ABaseEnemy>(OwnerActor);
	//	HealthBar->SetPercent(OwnerEnemy->Health/OwnerEnemy->MaxHealth * 100);
	//}
}

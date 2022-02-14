


#include "DashBars.h"
#include "Components/ProgressBar.h"

UDashBars::UDashBars(const FObjectInitializer& ObjectInitializer) : UUserWidget(ObjectInitializer) {
}

void UDashBars::NativeConstruct() {
	Super::NativeConstruct();

}

void UDashBars::UpdateStaminaBars(int32 Stamina, float RechargeTime, float CurrentTime) {
	// divide total stamina in 3.
	switch (Stamina) {
	case 0:
		StaminaBar3->SetPercent(0.f);
		StaminaBar2->SetPercent(0.f);
		StaminaBar1->SetPercent(CurrentTime/RechargeTime);
		break;
	case 1:
		StaminaBar3->SetPercent(0.f);
		StaminaBar2->SetPercent(CurrentTime/RechargeTime);
		break;
	case 2:
		StaminaBar3->SetPercent(CurrentTime/RechargeTime);
		break;
	default:
		break;
	}

	// fill bars from 1 to 3 with corresponding amount.
}




#include "AmmoBars.h"
#include "Components/ProgressBar.h"

UAmmoBars::UAmmoBars(const FObjectInitializer& ObjectInitializer) : UUserWidget(ObjectInitializer) {
}

void UAmmoBars::NativeConstruct() {
	Super::NativeConstruct();

}

void UAmmoBars::UpdateAmmoBars(int32 Ammo, int32 MaxAmmo) {
	// Fill stamina bars:
	
	if (Ammo <= float(MaxAmmo)/3) {
		AmmoBar3->SetPercent(0.f);
		AmmoBar2->SetPercent(0.f);
		AmmoBar1->SetPercent(float(Ammo)/(float(MaxAmmo)/3));
	}
	else if(Ammo <= 2*float(MaxAmmo)/3) {
		AmmoBar3->SetPercent(0.f);
		AmmoBar2->SetPercent((float(Ammo) - float(MaxAmmo) / 3) / (float(MaxAmmo) - 2 * float(MaxAmmo) / 3));
		AmmoBar1->SetPercent(1.f);
	}
	else {
		AmmoBar3->SetPercent((float(Ammo) - 2 * float(MaxAmmo) / 3) / (float(MaxAmmo) - 2 * float(MaxAmmo) / 3));
		AmmoBar2->SetPercent(1.f);
		AmmoBar1->SetPercent(1.f);
	}
}
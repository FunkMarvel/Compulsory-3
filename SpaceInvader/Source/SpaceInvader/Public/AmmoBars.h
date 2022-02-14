

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AmmoBars.generated.h"

/**
 * 
 */
UCLASS()
class SPACEINVADER_API UAmmoBars : public UUserWidget
{
	GENERATED_BODY()

public:
	UAmmoBars(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	void UpdateAmmoBars(int32 Ammo, int32 MaxAmmo);

protected:
	UPROPERTY(meta = (BindWidget))
		class UProgressBar* AmmoBar1;
	UPROPERTY(meta = (BindWidget))
		class UProgressBar* AmmoBar2;
	UPROPERTY(meta = (BindWidget))
		class UProgressBar* AmmoBar3;
};



#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DashBars.generated.h"

/**
 * 
 */
UCLASS()
class SPACEINVADER_API UDashBars : public UUserWidget
{
	GENERATED_BODY()

public:
	UDashBars(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	void UpdateStaminaBars(int32 Stamina, float RechargeTime, float CurrentTime);

protected:
	UPROPERTY(meta = (BindWidget))
		class UProgressBar* StaminaBar1;
	UPROPERTY(meta = (BindWidget))
		class UProgressBar* StaminaBar2;
	UPROPERTY(meta = (BindWidget))
		class UProgressBar* StaminaBar3;
};

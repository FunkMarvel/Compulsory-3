

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthBarWidget.generated.h"

UCLASS(Abstract)
class SPACEINVADER_API UHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget))
		class UProgressBar* HealthBar;
};

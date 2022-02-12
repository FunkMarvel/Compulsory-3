

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthBarWidget.generated.h"

UCLASS(Abstract)
class SPACEINVADER_API UHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	TWeakObjectPtr<AActor> OwnerActor;

	UPROPERTY(meta = (BindWidget))
		class UProgressBar* HealthBar;

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	void SetOwnerOfBar(AActor* SomeActor) {OwnerActor = SomeActor; }
};



#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "HealthBarWidget.generated.h"

UCLASS(Abstract)
class SPACEINVADER_API UHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UHealthBarWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;
	
protected:
	TWeakObjectPtr<AActor> OwnerActor;

	UPROPERTY(meta = (BindWidget))
		class UProgressBar* HealthBar;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	void SetOwnerOfBar(AActor* SomeActor) {OwnerActor = SomeActor; }
};

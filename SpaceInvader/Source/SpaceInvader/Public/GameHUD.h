

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Components/WidgetComponent.h"
#include "HealthBarWidget.h"
#include "GameHUD.generated.h"

/**
 * 
 */
UCLASS()
class SPACEINVADER_API AGameHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	AGameHUD();

	virtual void DrawHUD() override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	//UFUNCTION()
	//	void UpdateHealthBar(float percent);

	UFUNCTION()
		void UpdateDashBars(float percent);

	UPROPERTY(EditDefaultsOnly, Category="Widgets")
		TSubclassOf<UUserWidget> HealthBarClass;

private:
	UPROPERTY()
		UHealthBarWidget* HealthBar{nullptr};

	UPROPERTY()
		FIntPoint ViewSize{};
};

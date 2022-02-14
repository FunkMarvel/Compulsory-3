

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Components/WidgetComponent.h"
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
		void UpdateDashBars();

	UPROPERTY(EditDefaultsOnly, Category="Widgets")
		TSubclassOf<UUserWidget> HealthBarClass;

	UPROPERTY(EditDefaultsOnly, Category="Widgets")
		TSubclassOf<UUserWidget> DashBarsClass;

private:
	UPROPERTY()
		class UHealthBarWidget* HealthBar{nullptr};

	UPROPERTY()
		class UDashBars* DashBars{nullptr};

	UPROPERTY()
		FIntPoint ViewSize{};
};

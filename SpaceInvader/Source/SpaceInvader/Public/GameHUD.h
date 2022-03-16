

#pragma once

#include "CoreMinimal.h"
#include "HealthBarWidget.h"
#include "ScoreWidget.h"
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

	UFUNCTION()
		void UpdateDashBars();

	UFUNCTION()
		void UpdateAmmoBars();


	
	UPROPERTY(EditDefaultsOnly, Category="Widgets|HUD")
		TSubclassOf<UUserWidget> HealthBarClass;

	UPROPERTY(EditDefaultsOnly, Category="Widgets|HUD")
		TSubclassOf<UUserWidget> BossHealthBarClass;


	UPROPERTY(EditDefaultsOnly, Category="Widgets|HUD")
		TSubclassOf<UUserWidget> DashBarsClass;

	UPROPERTY(EditDefaultsOnly, Category="Widgets|HUD")
		TSubclassOf<UUserWidget> AmmoBarsClass;

	UPROPERTY(EditDefaultsOnly, Category="Widgets|Game state")
		TSubclassOf<UUserWidget> GameOverClass;

	UPROPERTY(EditDefaultsOnly, Category="Widgets|Game state")
		TSubclassOf<UUserWidget> GameWinClass;

	UPROPERTY(EditDefaultsOnly, Category="Widgets|Score")
	TSubclassOf<UScoreWidget> ScoreClass;

	void ViewGameOver(bool ShowGameOver);
	void ViewGameWin(bool ShowGameWin);

	class UHealthBarWidget* GetBossHealthBar(); 
	
private:
	UPROPERTY()
		class UHealthBarWidget* HealthBar{nullptr};

	UPROPERTY()
		class UHealthBarWidget* BossHealthBar{nullptr};
	
	UPROPERTY()
		class UDashBars* DashBars{nullptr};

	UPROPERTY()
		class UAmmoBars* AmmoBars{nullptr};

	UPROPERTY()
		class UGameOverWidget* GameOver{nullptr};

	UPROPERTY()
		class UGameOverWidget* GameWin{nullptr};

	UPROPERTY()
	class UScoreWidget* ScoreWidget{nullptr};

	UPROPERTY()
		FIntPoint ViewSize{};
};

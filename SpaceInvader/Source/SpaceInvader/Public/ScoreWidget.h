

#pragma once

#include "CoreMinimal.h"
#include "MainGameInstance.h"
#include "Blueprint/UserWidget.h"
#include "ScoreWidget.generated.h"

/**
 * 
 */
UCLASS()
class SPACEINVADER_API UScoreWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetLocalMainGameInstance(UMainGameInstance* NewMainGameInstance){MainGameInstance = NewMainGameInstance; }

	// is subscribed to a Multicast event from main game instance.
	UFUNCTION()
	void UpdateScoreWidget(int32 Score);
private:

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text = nullptr;
	UPROPERTY()
	UMainGameInstance* MainGameInstance = nullptr;
	
	
protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};

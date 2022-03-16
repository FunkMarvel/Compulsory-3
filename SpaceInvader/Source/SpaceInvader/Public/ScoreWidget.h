

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
	
private:

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text = nullptr;
	UPROPERTY()
	UMainGameInstance* MainGameInstance = nullptr;
	
	
protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};

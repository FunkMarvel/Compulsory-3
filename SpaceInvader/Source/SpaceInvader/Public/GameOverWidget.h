

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "GameOverWidget.generated.h"

/**
 * 
 */
UCLASS()
class SPACEINVADER_API UGameOverWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UGameOverWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;
	void AddOnPress();
	
protected:
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* GameOverMessage;

	UPROPERTY (meta = (BindWidget))
		UButton* RestartGameButton;
};

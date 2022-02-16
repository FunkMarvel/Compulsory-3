

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
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
	
protected:
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* GameOverMessage;
};




#include "ScoreWidget.h"

#include <string>

#include "MainGameInstance.h"
#include "Components/TextBlock.h"

void UScoreWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (MainGameInstance != nullptr)
	{
		
		int32 Score = MainGameInstance->GetScore();
		Text->SetText(FText::AsNumber(19238192));
	}
}

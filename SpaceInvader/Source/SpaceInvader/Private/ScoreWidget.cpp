


#include "ScoreWidget.h"

#include <string>

#include "MainGameInstance.h"
#include "Components/TextBlock.h"
#include "GameFramework/GameMode.h"
#include "SpaceInvader/SpaceInvaderGameModeBase.h"


void UScoreWidget::UpdateScoreWidget(int32 Score)
{
	Text->SetText(FText::AsNumber(Score));
}

void UScoreWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	/*if (MainGameInstance != nullptr)
	{
		
		int32 Score = MainGameInstance->GetScore();
		Text->SetText(FText::AsNumber());
	}*/
	/*AGameModeBase* ModeBase = GetWorld()->GetAuthGameMode();
	if (ModeBase->IsA(ASpaceInvaderGameModeBase::StaticClass()))
	{
		ASpaceInvaderGameModeBase* SkyRiderGameMode = Cast<ASpaceInvaderGameModeBase>(ModeBase);
		Text->SetText(FText::AsNumber(SkyRiderGameMode->GetScore()));
		
	}*/
}

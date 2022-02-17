


#include "GameOverWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "../SpaceInvaderGameModeBase.h"

UGameOverWidget::UGameOverWidget(const FObjectInitializer& ObjectInitializer) : UUserWidget(ObjectInitializer) {

}

void UGameOverWidget::NativeConstruct() {
	Super::NativeConstruct();

}

void UGameOverWidget::AddOnPress() {
	ASpaceInvaderGameModeBase* GameMode = Cast<ASpaceInvaderGameModeBase>(GetWorld()->GetAuthGameMode());

	RestartGameButton->OnClicked.AddDynamic(GameMode, &ASpaceInvaderGameModeBase::OnResetGamePress);
}

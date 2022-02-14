
#pragma once

#include "CoreMinimal.h"
#include "BaseEnemy.h"
#include "HulkBossEnemy.generated.h"

/**
 * 
 */
UCLASS()
class SPACEINVADER_API AHulkBossEnemy : public ABaseEnemy
{
	GENERATED_BODY()
	
public:
	AHulkBossEnemy();

	//TArray<class UStaticMeshComponent> SpinnerMeshes = nullptr;
	//UPROPERTY(EditAnywhere) TArray<class UStaticMeshComponent*> SpinnerMeshes;
	UPROPERTY(EditAnywhere) 
		class UStaticMeshComponent* Spinner1;
private:
	
	enum HulkState {
		Normal,
		ClosingBeam
	};
	HulkState currentState = HulkState::Normal;
	float StartOfStateTime = 0.f;
	bool bEnterState = false;

	UFUNCTION()
	void NormalState();
	UFUNCTION()
	void ClosingBeamState();

	
	void ChangeCurrentState(HulkState NewState);

	// Closing Beam state
	FVector Direction = FVector::ZeroVector;
	UPROPERTY(EditAnywhere, Category = "Enemy | Closing Beam")
		float ClosingBeamDuration;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	

	UPROPERTY(EditAnywhere)
		class UCurveFloat* CURVETEST;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};

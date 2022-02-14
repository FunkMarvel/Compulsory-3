
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
		ClosingBeam,
		RotatingBeam
	};
	HulkState currentState = HulkState::Normal;
	float StartOfStateTime = 0.f;
	bool bEnterState = false;

	UFUNCTION()
	void NormalState();
	UFUNCTION()
	void ClosingBeamState();
	UFUNCTION()
	void RotateBeamState();

	
	void ChangeCurrentState(HulkState NewState);

	// Closing Beam state
	FVector ClosingBeamDirection = FVector::ZeroVector;
	UPROPERTY(EditAnywhere, Category = "Enemy | Closing Beam")
		float ClosingBeamDuration;
	UPROPERTY(EditAnywhere, Category = "Enemy | Closing Beam")
		float ClosingBeamCooldown;
	
	// Rotating Beam state
	FVector RotatingBeamDirection = FVector::ZeroVector;
	UPROPERTY(EditAnywhere, Category = "Enemy | Rotating beam")
		float RotatingBeamDuration;
	UPROPERTY(EditAnywhere, Category = "Enemy | Rotating beam")
		float RotatingBeamCooldown;


	int32 NextBeamIndex = 0.f;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	

	UPROPERTY(EditAnywhere)
	class UCurveFloat* ClosingBeamCurve;
	UPROPERTY(EditAnywhere)
	class UCurveFloat* RotatingBeamCurve;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};

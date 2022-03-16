
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

	// Hulk Meshes 
	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* SpinnerOne = nullptr;
	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* SpinnerTwo = nullptr;
	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* SpinnerThree = nullptr;
	
	// Spinner speed
	UPROPERTY(EditDefaultsOnly, Category = "Enemy|SpinnerSpeed")
	float SpinnerBaseSpeed = 300.f;
	UPROPERTY(EditDefaultsOnly, Category = "Enemy|SpinnerSpeed")
	float SpinnerAttackModifier = 500.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning|Level Gate")
		TSubclassOf<class ALevelGate> GateClass;

	UFUNCTION()
	void SpinBlades(float Speed);

	//handle destruction
	virtual void HandleDestruction() override;

	// scaling meshes
	UFUNCTION()
		void ScaleSpinner(UStaticMeshComponent* MeshComp, const float Scale, const float Alpha);
	UPROPERTY(EditDefaultsOnly, Category = "Enemy|Scale")
	float AttackingScale;
	
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
	UPROPERTY(EditDefaultsOnly, Category = "Enemy|Closing Beam")
		float ClosingBeamDuration;
	UPROPERTY(EditDefaultsOnly, Category = "Enemy|Closing Beam")
		float ClosingBeamCooldown;
	
	// Rotating Beam state
	FVector RotatingBeamDirection = FVector::ZeroVector;
	UPROPERTY(EditDefaultsOnly, Category = "Enemy|Rotating beam")
		float RotatingBeamDuration;
	UPROPERTY(EditDefaultsOnly, Category = "Enemy|Rotating beam")
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

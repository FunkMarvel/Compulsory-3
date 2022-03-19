

#pragma once

#include "CoreMinimal.h"
#include "BaseEnemy.h"
#include "FinalBossEnemy.generated.h"

/**
 * 
 */
UCLASS()
class SPACEINVADER_API AFinalBossEnemy : public ABaseEnemy
{
	GENERATED_BODY()

public:
	AFinalBossEnemy();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(VisibleAnywhere, Category = "Collider|Limbs")
	class UCapsuleComponent* LeftSideCapsuleComp = nullptr;
	
	UPROPERTY(VisibleAnywhere, Category = "Collider|Limbs")
	class UCapsuleComponent* RightSideCapsuleComp = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Enemy|Wings")
	class UStaticMeshComponent* LeftSideMesh;
	
	UPROPERTY(EditDefaultsOnly, Category = "Enemy|Wings")
	class UStaticMeshComponent* RightSideMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat|Beams")
	class ULaserBeamComponent* LeftLaserBeamComp{nullptr};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat|Beams")
	class ULaserBeamComponent* RightLaserBeamComp{nullptr};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat|Beams")
	class UParticleSystemComponent* LeftLaserBeamParticle{nullptr};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat|Beams")
	class UParticleSystemComponent* RightLaserBeamParticle{nullptr};
	
protected:
	UPROPERTY(EditAnywhere, Category="Enemy|Wings")
	float WingOffset{300.f};

	UPROPERTY(EditAnywhere, Category="Combat")
	float TimeToChangeAttack{10};
	float AttackTimer{0};

	enum EBossState
	{
		Normal,
		DirectFire,
		ClosingBeam,
		RotatingBeam
	};

	enum EBossPart
	{
		Left = -1,
		Middle = 0,
		Right = 1
	};

	EBossState CurrentState{EBossState::Normal};

	UFUNCTION()
	void NormalState();

	UFUNCTION()
	void DirectFireState();

	UFUNCTION()
	void ClosingBeamState();

	UFUNCTION()
	void RotateBeamState();
	
	virtual void OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	void ChangeCurrentState(EBossState NewState) {CurrentState = NewState;}

	// using wings:
	void RotateBossPart(EBossPart PartToRotate, FRotator NewRotation);
	FVector GetLeftDirToPlayer();
	FVector GetRightDirToPlayer();
	
	void FireFromPart(EBossPart PartToFireFrom);
	bool bFireFromLeft{true};

	void SetBeamsOn(bool bBeamsOn);
	float TimeToCloseBeams{2};
	float CloseBeamTimer{0};
	FVector FinalBeamDirection{};
};

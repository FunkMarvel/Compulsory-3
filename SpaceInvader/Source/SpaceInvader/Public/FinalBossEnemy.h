

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

protected:
	UPROPERTY(EditAnywhere, Category="Enemy|Wings")
	float WingOffset{300.f};
};

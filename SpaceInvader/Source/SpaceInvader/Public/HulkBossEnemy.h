
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


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	float StartOfShotTime = 0.f;

	UPROPERTY(EditAnywhere)
		class UCurveFloat* CURVETEST;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};

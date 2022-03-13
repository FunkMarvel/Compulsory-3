

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelGate.generated.h"

UCLASS()
class SPACEINVADER_API ALevelGate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelGate();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category="Collider")
		class UCapsuleComponent* Collider{nullptr};

	UPROPERTY(EditAnywhere, Category="Portal mesh")
		class UStaticMeshComponent* PortalMesh{nullptr};

	UPROPERTY(EditAnywhere, Category="Levels")
		TArray<FString> Levels;

public:
	UFUNCTION()
	void ChangeLevel(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
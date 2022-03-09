

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupItem.generated.h"

UCLASS()
class SPACEINVADER_API APickupItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupItem();
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, Category="Mesh")
		class UStaticMeshComponent* CosmeticMeshComponent{nullptr};

	UPROPERTY(VisibleAnywhere, Category="Mesh")
		class UCapsuleComponent* CapsuleComponent{nullptr};

protected:
	UPROPERTY(VisibleAnywhere, Category="Properties");
		int32 ScoreValue{100};

	UFUNCTION()
		virtual void ApplyEffect();

};

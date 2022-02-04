// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletActor.generated.h"

UCLASS()
class SPACEINVADER_API ABulletActor : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ABulletActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category = "Bullet Properties")
		float Speed{1000.f};

	UPROPERTY(EditAnywhere, Category = "Bullet Properties")
		float TimeBeforeDestroy{5.f};

	UPROPERTY(EditAnywhere, Category = "Bullet Properties")
		float LifeTime{0.f};

	UPROPERTY(EditAnywhere, Category = "Bullet Properties")
		UParticleSystem* BulletFireFX{nullptr};

	UPROPERTY(EditAnywhere, Category = "Bullet Properties")
		USoundBase* BulletFireSound{nullptr};

	/*int score;*/

	//UFUNCTION()
		//void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent)
};

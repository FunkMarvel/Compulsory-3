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
	UPROPERTY(EditDefaultsOnly, Category = "Bullet Properties")
		float Speed{1000.f};

	UPROPERTY(EditDefaultsOnly, Category = "Bullet Properties")
		float TimeBeforeDestroy{5.f};

	UPROPERTY(EditDefaultsOnly, Category = "Bullet Properties")
		float LifeTime{0.f};

	UPROPERTY(EditDefaultsOnly, Category = "Bullet Properties")
		UParticleSystem* BulletFireFX{nullptr};

	UPROPERTY(EditDefaultsOnly, Category = "Bullet Properties")
		USoundBase* BulletFireSound{nullptr};

};

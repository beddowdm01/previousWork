// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AsteroidSpawner.generated.h"

UCLASS()
class CPPGAME_API AAsteroidSpawner : public AActor
{
	GENERATED_BODY()
	
private:
    int CurrentNoAsteroids;
public:	
	// Sets default values for this actor's properties
	AAsteroidSpawner();
  ~AAsteroidSpawner();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
  //random asteroid spawn locations
  float RandX;
  float RandY;
  float RandZ;

  int RandAsteroid;//random asteroid number

  bool BCanSpawn = true;
  FTimerHandle SpawnAsteroidHandle;//timer handle for reseting can spawn

  //Uproperties for start settings
      UPROPERTY(EditAnywhere, Category = "Start Settings")
          int MaxAsteroids = 10;
      UPROPERTY(EditAnywhere, Category = "Start Settings")
          FVector StartArea;
      UPROPERTY(EditAnywhere, Category = "Start Settings")
          FVector EndArea;
      UPROPERTY(EditAnywhere, Category = "Start Settings")
          int SpawnDelay = 1;
      //Uproperty asteroid class array
      UPROPERTY(EditAnywhere, Category = "Asteroids")
      TArray<TSubclassOf<class AAsteroid>> Asteroids;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
  void DecrementAsteroids();
  void ResetSpawn();
  UFUNCTION()
      void SpawnAsteroid(TSubclassOf<AAsteroid> PassedAsteroid);//spawns an asteroid of the class hat is passed
       
};

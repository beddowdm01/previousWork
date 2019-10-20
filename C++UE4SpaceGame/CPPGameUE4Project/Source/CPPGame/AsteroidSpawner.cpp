//Daniel Beddow, 20/10/2019. Asteroid spawner class that spawns asteroids


#include "AsteroidSpawner.h"
#include "Asteroid.h"
#include "Math/UnrealMathUtility.h"
#include "Containers/Array.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "TimerManager.h"

// Sets default values
AAsteroidSpawner::AAsteroidSpawner()
{
	PrimaryActorTick.bCanEverTick = true;
}

AAsteroidSpawner::~AAsteroidSpawner()
{

}

// Called when the game starts or when spawned
void AAsteroidSpawner::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AAsteroidSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
  //sets a random spawn location for asteroids
     RandX = (FMath::FRandRange(StartArea.X, EndArea.X));
     RandY = (FMath::FRandRange(StartArea.Y, EndArea.Y));
     RandZ = (FMath::FRandRange(StartArea.Z, EndArea.Z));

     //sets a random asteroid from the asteroid classes
     RandAsteroid = FMath::RandRange(0, (Asteroids.Num()-1));
     RandAsteroid = (int)RandAsteroid;

  if (BCanSpawn) //if it can spawn
  {
      BCanSpawn = false;
      if (Asteroids[RandAsteroid])//if the asteroid class exists in the array
      {
          SpawnAsteroid(Asteroids[RandAsteroid]);//spawns the asteroid
          //resets spawn every .23 seconds
          GetWorld()->GetTimerManager().SetTimer(SpawnAsteroidHandle, this, &AAsteroidSpawner::ResetSpawn, .25f, false);
      }
  }
}

void AAsteroidSpawner::DecrementAsteroids()//decrements the asteroid counter
{
    CurrentNoAsteroids--;

}

void AAsteroidSpawner::ResetSpawn()//resets spawn bool to true
{
    BCanSpawn = true;
}

void AAsteroidSpawner::SpawnAsteroid(TSubclassOf<AAsteroid> PassedAsteroid)//spawns asteroids
{
    if (CurrentNoAsteroids < MaxAsteroids)//if the current asteroids are not the max amount
    {
        if (PassedAsteroid)//if the passedasteroid exists
        {
            //creates spawn parameters
            FActorSpawnParameters SpawnParams;
            SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
            SpawnParams.bNoFail = true;
            SpawnParams.Owner = this;
            //creates spawn transform
            FTransform AsteroidSpawnTransform;
            FVector SpawnLocation;
            SpawnLocation.X = RandX;
            SpawnLocation.Y = RandY;
            SpawnLocation.Z = RandZ;
            AsteroidSpawnTransform.SetLocation(SpawnLocation);
            AsteroidSpawnTransform.SetScale3D(FVector(1.0f));
            //spawns the asteroid
            GetWorld()->SpawnActor<AAsteroid>(PassedAsteroid, AsteroidSpawnTransform, SpawnParams);
            GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
        }
        CurrentNoAsteroids++;//increments asteroid counter
    }
}



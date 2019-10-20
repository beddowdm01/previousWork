//Daniel Beddow, 20/10/2019. Asteroid class with asteroid movement and collision


#include "Asteroid.h"
#include "Classes/Components/SphereComponent.h"
#include "Classes/GameFramework/ProjectileMovementComponent.h"
#include "Paper2D/Classes/PaperSpriteComponent.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Spaceship.h"
#include "AsteroidSpawner.h"
#include "CPPGameMode.h"

// Sets default values
AAsteroid::AAsteroid()
{
	PrimaryActorTick.bCanEverTick = true;

  //Creates the asteroid collision and sets as root component
  AsteroidCollision = CreateDefaultSubobject<USphereComponent>("Sphere Collision");
  AsteroidCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
  AsteroidCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
  SetRootComponent(AsteroidCollision);

  //Creates the asteroid sprite and with rotation so it can be seen in game
  AsteroidSprite = CreateDefaultSubobject<UPaperSpriteComponent>("Sprite");
  FRotator SpriteRotator;
  SpriteRotator.Yaw = -90.0f;
  SpriteRotator.Pitch = 0;
  SpriteRotator.Roll = 0;
  AsteroidSprite->AddLocalRotation(SpriteRotator);
  AsteroidSprite->SetupAttachment(AsteroidCollision);

  //Creates the asteroid movement setting defaults.
  AsteroidMovement = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile movement");
  AsteroidMovement->InitialSpeed = 1000.0f;
  AsteroidMovement->MaxSpeed = 1000.0f;
  AsteroidMovement->ProjectileGravityScale = 0.0f;
  AsteroidMovement->Velocity.X = 0.0f;
  AsteroidMovement->Velocity.Y = 0.0f;
  AsteroidMovement->Velocity.Z = -10.0f;

//Calls the function OnAsteroidHit when the actor is hit
  OnActorHit.AddDynamic(this, &AAsteroid::OnAsteroidHit);
}

AAsteroid::~AAsteroid()
{

}

// Called when the game starts or when spawned
void AAsteroid::BeginPlay()
{
	Super::BeginPlay();
  //The Spawner is set as the asteroid spawner which spawned the asteroid
  Spawner = (AAsteroidSpawner*)this->GetOwner();
}

void AAsteroid::OnAsteroidHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
    //If the asteroid collided with a spaceship: deactivate spaceship and destroy the asteroid and spawn explosion
    if (ASpaceship* Spaceship = Cast<ASpaceship>(OtherActor))
     {
        Spaceship->DeactivateSpaceship();
         if (Spawner) {
             Spawner->DecrementAsteroids();//decrement asteroids
         }
         ExplodeAsteroid();
         Destroy();
     }
    //If it collided with another asteroid destroy itself
    else if (AAsteroid* Asteroid = Cast<AAsteroid>(OtherActor))
    {     
        if (Spawner) {
            Spawner->DecrementAsteroids();//decrement asteroids
        }
        Destroy();
    }
    //If it collided with anything else destroy itself
    else
    {
        if (Spawner) {
            Spawner->DecrementAsteroids();//decrement asteroids
        }
        if (ACPPGameMode* GameMode = Cast<ACPPGameMode>(GetWorld()->GetAuthGameMode()))
        {
            GameMode->AddScore(10);
        }
        Destroy();
    }
}

// Called every frame
void AAsteroid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//spawns an explosion at the location of the asteroid
void AAsteroid::ExplodeAsteroid()
{
    if (Explosion)//If the explosion class is set
    {
        //sets the spawn parameters
        FActorSpawnParameters SpawnParams;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
        SpawnParams.bNoFail = true;
        SpawnParams.Owner = this;

        //set the spawn transform of the explosion = to the asteroid
        FTransform ExplosionSpawnTransform;
        ExplosionSpawnTransform.SetLocation(GetActorLocation());
        ExplosionSpawnTransform.SetRotation(GetActorRotation().Quaternion());
        ExplosionSpawnTransform.SetScale3D(FVector(1.0f));
        //Spawn the explosion
        GetWorld()->SpawnActor<AActor>(Explosion, ExplosionSpawnTransform, SpawnParams);
    }
}


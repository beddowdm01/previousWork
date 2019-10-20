//Daniel Beddow, 20/10/2019. Bullet class that is shot from the spaceship

#include "Bullet.h"
#include "Classes/GameFramework/ProjectileMovementComponent.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Classes/Components/CapsuleComponent.h"
#include "Paper2D/Classes/PaperSpriteComponent.h"
#include "Spaceship.h"
#include "Asteroid.h"
#include "Kismet/GameplayStatics.h"
#include "CPPGameMode.h"

// Sets default values
ABullet::ABullet()
{
    PrimaryActorTick.bCanEverTick = true;
//gets the player characyer
  ACharacter* MyCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
  //Creates bullet collision
  BulletCollision = CreateDefaultSubobject<UCapsuleComponent>("Capsule Collision");
  BulletCollision->MoveIgnoreActors.Add((AActor*)MyCharacter);
  BulletCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
  BulletCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
  SetRootComponent(BulletCollision);
  //Creates bullet sprite and rotates it 90 degrees so it can be seen
  BulletSprite = CreateDefaultSubobject<UPaperSpriteComponent>("Sprite");
  FRotator SpriteRotator;
  SpriteRotator.Yaw = -90.0f;
  SpriteRotator.Pitch = 0;
  SpriteRotator.Roll = 0;
  BulletSprite->AddLocalRotation(SpriteRotator);
  BulletSprite->SetRelativeScale3D(FVector(0.05f,0.05f,0.05f));
  BulletSprite->SetupAttachment(BulletCollision);

  //Creates bullet movement from projectile movement and sets velocities
  BulletMovement = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile movement");
  BulletMovement->InitialSpeed = 2000.0f;
  BulletMovement->MaxSpeed = 2000.0f;
  BulletMovement->ProjectileGravityScale = 0.0f;
  BulletMovement->Velocity.Z = 1.0f;
  BulletMovement->Velocity.X = 0.0f;

  OnActorHit.AddDynamic(this, &ABullet::OnBulletHit);//calls OnBulletHit when actor is hit.
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//When the bullet hits an actor.
void ABullet::OnBulletHit(AActor * SelfActor, AActor * OtherActor, FVector NormalImpulse, const FHitResult & Hit)
{
   if (AAsteroid* Asteroid = Cast<AAsteroid>(OtherActor))//If it is an asteroid
    {
        if (ACPPGameMode* GameMode = Cast<ACPPGameMode>(GetWorld()->GetAuthGameMode()))//Add score to the game mode
        {
            GameMode->AddScore(50);
        }
        Asteroid->ExplodeAsteroid();//Explodes the asteroid
    }
   Destroy();//Destroys the bullet
}


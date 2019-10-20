//Daniel Beddow, 20/10/2019. Deathzone class that kills player when collides to prevent out of bounds.


#include "DeathZone.h"
#include "Spaceship.h"
#include "Classes/Components/BoxComponent.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/Actor.h"

// Sets default values
ADeathZone::ADeathZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
  //Creates the collision and sets it as root component
  Collision = CreateDefaultSubobject<UBoxComponent>("Collision");
  Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
  Collision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
  Collision->CanCharacterStepUpOn = ECB_No;
  SetRootComponent(Collision);
  //On actor overlap calls OnDeathZoneOverlap
  OnActorBeginOverlap.AddDynamic(this, &ADeathZone::OnDeathZoneOverlap);
}

// Called when the game starts or when spawned
void ADeathZone::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADeathZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADeathZone::OnDeathZoneOverlap(AActor * SelfActor, AActor * OtherActor)
{
    if (ASpaceship* Spaceship = Cast<ASpaceship>(OtherActor))//if it is the spaceship
    {
        Spaceship->DeactivateSpaceship();//Deactivates the spaceship player
    }
}
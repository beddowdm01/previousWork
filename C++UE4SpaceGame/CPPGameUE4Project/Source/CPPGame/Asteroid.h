//Daniel Beddow, 20/10/2019
//Asteroid class header with asteroid movement and collision

#pragma once
#include "Paper2D/Classes/PaperSpriteComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Asteroid.generated.h"


UCLASS()
class CPPGAME_API AAsteroid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAsteroid();
  ~AAsteroid();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


  class AAsteroidSpawner* Spawner;  //Ptr to the asteroid spawner class

  //Uproperties of the UComponents
  UPROPERTY(EditAnywhere, Category = "Component")
      class USphereComponent* AsteroidCollision;
  UPROPERTY(EditAnywhere, Category = "Component")
      class UPaperSpriteComponent* AsteroidSprite;
  UPROPERTY(EditAnywhere, Category = "Component")
      class UProjectileMovementComponent* AsteroidMovement;
  UPROPERTY(EditAnywhere, Category = "Components")
      TSubclassOf<class AActor> Explosion;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
  void ExplodeAsteroid();//Function to explode the asteroid
  UFUNCTION()//When the Asteroid is hit
  void OnAsteroidHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);
};

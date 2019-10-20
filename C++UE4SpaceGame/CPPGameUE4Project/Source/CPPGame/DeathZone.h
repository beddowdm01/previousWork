//Daniel Beddow, 20/10/2019. Deathzone class header that kills player

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DeathZone.generated.h"

UCLASS()
class CPPGAME_API ADeathZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADeathZone();
  //Uproperty under category collision
  UPROPERTY(EditAnywhere, Category = "Components")
      class UBoxComponent* Collision;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
  UFUNCTION()
  void OnDeathZoneOverlap(AActor* SelfActor, AActor* OtherActor);//deactivates spaceship when collides with it.
};

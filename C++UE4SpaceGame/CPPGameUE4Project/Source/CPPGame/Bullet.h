//Daniel Beddow, 20/10/2019. Bullet class header.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class CPPGAME_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

protected:
    //Uproperties bullet components
    UPROPERTY(EditAnywhere, Category = "Component")
        class UProjectileMovementComponent* BulletMovement;
    UPROPERTY(EditAnywhere, Category = "Component")
        class UCapsuleComponent* BulletCollision;
    UPROPERTY(EditAnywhere, Category = "Component")
        class UPaperSpriteComponent* BulletSprite;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
  UFUNCTION()
  void OnBulletHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);//when the bullet hits an object
};

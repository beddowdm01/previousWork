//Daniel Beddow, 20/10/2019. Asteroid class header with asteroid movement and collision

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Spaceship.generated.h"

UCLASS()
class CPPGAME_API ASpaceship : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASpaceship();
  //Uproperties for sprites and collision
  UPROPERTY(EditAnywhere, Category = "Components")
      class UPaperSpriteComponent* Sprite;
  UPROPERTY(EditAnywhere, Category = "Components")
      class UCapsuleComponent* Collision;

  bool BCanFire = true;
  bool Destroyed = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
  bool IsPaused = false;

  FRotator SpriteRotator;
  FTimerHandle CanFireHandle;
  FTimerHandle RestartHandle;

  //Uproperties for spaceship movement
  UPROPERTY(EditAnywhere, Category = "Movement")
      float MaximumSpeed = 5000;
  UPROPERTY(EditAnywhere, Category = "Movement")
      float StrafeSpeed = 300;
  UPROPERTY(EditAnywhere, Category = "Movement")
      float Speed = 500;
  UPROPERTY(EditAnywhere, Category = "Movement")
      float BackwardsSpeed = 50;
  //Uproperties for camera
  UPROPERTY(EditAnywhere, Category = "Camera")
      FVector CamOffset = FVector(0, 0, 250);
  UPROPERTY(EditAnywhere, Category = "Camera")
      float CameraArmLength = 1000.0f;

  //Uproperties for shooting
  UPROPERTY(EditAnywhere, Category = "Shooting")
      TSubclassOf<class ABullet> BulletClass;

  //Uproperties for components
  UPROPERTY(EditAnywhere, Category = "Components")
  class UCameraComponent* Camera;
  UPROPERTY(EditAnywhere, Category = "Components")
  class USpringArmComponent* CameraArm;
  UPROPERTY(EditAnywhere, Category = "Components")
  TSubclassOf<class AActor> Explosion;
  UPROPERTY(EditAnywhere, Category = "Components")
  class UFloatingPawnMovement* FloatingPawnMovement;

  //Uproperties for sounds
  UPROPERTY(EditAnywhere, Category = "Sounds")
      USoundBase* RocketSound;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
  void ResetFire();//Resets fire bool top true
  void DeactivateSpaceship();//deactives spaceship when it is hit
  void SpawnExplosion();//spawns an explosion
  void Forward(float Amount);//moves forward
  void Strafe(float Amount);//strafes
  void Shoot();//shoots a bullet from bullet class
  void Pause();//pauses the game
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;//sets up player input
};

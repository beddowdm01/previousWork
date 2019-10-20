//Daniel Beddow, 20/10/2019. Asteroid class with asteroid movement and collision

#include "Spaceship.h"
#include "Classes/GameFramework/floatingPawnMovement.h"
#include "Classes/GameFramework/SpringArmComponent.h"
#include "Classes/Camera/CameraComponent.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Classes/Components/InputComponent.h"
#include "Paper2D/Classes/PaperSpriteComponent.h"
#include "Classes/Components/CapsuleComponent.h"
#include "Bullet.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "CPPGameHUD.h"
#include "CPPGameMode.h"

// Sets default values
ASpaceship::ASpaceship()
{
	PrimaryActorTick.bCanEverTick = true;
  //Creates the spaceship collision and sets it as the root component
  Collision = CreateDefaultSubobject<UCapsuleComponent>("Collision");
  Collision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
  Collision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
  Collision->SetCapsuleHalfHeight(66.0f);
  Collision->SetCapsuleRadius(33.0f);
  Collision->CanCharacterStepUpOn = ECB_No;
  SetRootComponent(Collision);
  //Creates the spaceship sprite and rotates it 90 degress so it can be seen
  Sprite = CreateDefaultSubobject<UPaperSpriteComponent>("Sprite");
  Sprite->SetRelativeScale3D(FVector(0.1f, 0.1f, 0.1f));
  SpriteRotator.Yaw = -90.0f;
  SpriteRotator.Pitch = 0;
  SpriteRotator.Roll = 0;
  Sprite->AddLocalRotation(SpriteRotator);
  Sprite->CanCharacterStepUpOn = ECB_No;
  Sprite->SetupAttachment(Collision);
  Sprite->RecreateRenderState_Concurrent();
  //Creates the spaceship movement
  FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>("Character Movement");
  FloatingPawnMovement->MaxSpeed = MaximumSpeed;
  //Creates a springarm component and sets its length
  CameraArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
  CameraArm->TargetArmLength = CamOffset.Z;
  //Creates the camera component and sets the expsoure brightness to improve visibility
  Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
  Camera->SetupAttachment(CameraArm);
  Camera->ProjectionMode = ECameraProjectionMode::Orthographic;
  Camera->OrthoWidth = 1920.0f;
  Camera->PostProcessSettings.bOverride_AutoExposureMaxBrightness = true;
  Camera->PostProcessSettings.bOverride_AutoExposureMinBrightness = true;
  Camera->PostProcessSettings.AutoExposureMaxBrightness = 20.0f;
  Camera->PostProcessSettings.AutoExposureMinBrightness = 0.0f;

}

// Called when the game starts or when spawned
void ASpaceship::BeginPlay()
{
	Super::BeginPlay();
  //Sets the location of the spring arm.
  CameraArm->SetWorldLocation(Collision->GetComponentLocation() + FVector(CamOffset));

}

// Called every frame
void ASpaceship::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



void ASpaceship::Forward(float Amount)//moves the spaceship upwards
{
    if (Amount == 1)
    {
        FloatingPawnMovement->AddInputVector(GetActorUpVector() * (Amount*Speed));
    }
    else if (Amount == -1)
    {
        FloatingPawnMovement->AddInputVector(GetActorUpVector() * (Amount*BackwardsSpeed));
    }

}

void ASpaceship::Strafe(float Amount)
{
    //UE_LOG(LogTemp, Warning, TEXT("Your message"));
    FloatingPawnMovement->AddInputVector(GetActorRightVector() * (Amount*StrafeSpeed));
}

void ASpaceship::Shoot()//shoots a bullet
{
    if (BCanFire) //if it can fire
    {
        BCanFire = false;
        if (!Destroyed)//if the spaceship is not destroyed
        {
            if (BulletClass)
            {
                //bullet spawn params
                FActorSpawnParameters SpawnParams;
                SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
                SpawnParams.bNoFail = true;
                SpawnParams.Owner = this;
                SpawnParams.Instigator = this;

                //bullet spawn transform
                FTransform BulletSpawnTransform;
                BulletSpawnTransform.SetLocation(GetActorUpVector() * 150.0f + GetActorLocation());
                BulletSpawnTransform.SetRotation(GetActorRotation().Quaternion());
                BulletSpawnTransform.SetScale3D(FVector(1.0f));

                //Plays Sounds
                UGameplayStatics::PlaySound2D(GetWorld(), RocketSound, 0.5f, 1.0f, 0.0f);

                //Spawns a bullet from the bullet class
                GetWorld()->SpawnActor<ABullet>(BulletClass, BulletSpawnTransform, SpawnParams);
            }
        }
        //calls the function ResetFire after 1.5 seconds
        GetWorld()->GetTimerManager().SetTimer(CanFireHandle, this, &ASpaceship::ResetFire, 1.5f, false);
    }

}



void ASpaceship::ResetFire()//sets the canfire bool to true
{
    BCanFire = true;
}

void ASpaceship::DeactivateSpaceship()//If the spaceship has been hit turns off visibility and collision
{
    //sets collision and visibility of sprite to false.
    Sprite->SetVisibility(false);
    Sprite->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    Sprite->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    //sets collision to false.
    Collision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    Collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    //is destroyed and cannot fire.
    Destroyed = true;
    BCanFire = false;
    //Gets the Hud
    ACPPGameHUD * HUD = Cast<ACPPGameHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
    //Gets the Gamemode
    ACPPGameMode* GM = Cast<ACPPGameMode>(GetWorld()->GetAuthGameMode());
    //pauses the game 2 seconds after the spaceship was destroyed
    GetWorld()->GetTimerManager().SetTimer(RestartHandle, this, &ASpaceship::Pause, 2.0f, false);
    HUD->GameOver();
    GM->SpaceshipDestroyed = true;
    SpawnExplosion();//spawns an explosion
}

void ASpaceship::SpawnExplosion()
{
    if (Explosion)//if the explosion class is set
    {
        FActorSpawnParameters SpawnParams;//sets spawnparameters of explosion
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
        SpawnParams.bNoFail = true;
        SpawnParams.Owner = this;
        SpawnParams.Instigator = this;

        FTransform ExplosionSpawnTransform;//sets spawn tranform of explosion
        ExplosionSpawnTransform.SetLocation(GetActorLocation());
        ExplosionSpawnTransform.SetRotation(GetActorRotation().Quaternion());
        ExplosionSpawnTransform.SetScale3D(FVector(1.0f));

        GetWorld()->SpawnActor<AActor>(Explosion, ExplosionSpawnTransform, SpawnParams);//spawns explosion
    }
}

void ASpaceship::Pause()//pauses the game
{
    APlayerController* const MyPlayer = Cast<APlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));
    IsPaused = !IsPaused;
    if (MyPlayer)//if the player controller exists
    {
        MyPlayer->SetPause(IsPaused);
    }
}

// Called to bind functionality to input
void ASpaceship::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
  PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &ASpaceship::Shoot);//sets shoot

  PlayerInputComponent->BindAxis("Forward", this, &ASpaceship::Forward);//sets forward movement
  PlayerInputComponent->BindAxis("Strafe", this, &ASpaceship::Strafe);//sets strafe input
}


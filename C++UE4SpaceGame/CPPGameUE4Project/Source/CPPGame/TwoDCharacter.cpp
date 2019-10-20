// Fill out your copyright notice in the Description page of Project Settings.


#include "TwoDCharacter.h"
#include "Classes/GameFramework/floatingPawnMovement.h"
#include "Classes/GameFramework/SpringArmComponent.h"
#include "Classes/Camera/CameraComponent.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Classes/Components/InputComponent.h"

// Sets default values
ATwoDCharacter::ATwoDCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATwoDCharacter::BeginPlay()
{
	Super::BeginPlay();

  Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
  CameraArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
  FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>("Character Movement");

	
}

// Called every frame
void ATwoDCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATwoDCharacter::Boost()
{
}

// Called to bind functionality to input
void ATwoDCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


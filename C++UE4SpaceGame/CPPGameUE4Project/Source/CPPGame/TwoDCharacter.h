// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TwoDCharacter.generated.h"

UCLASS()
class CPPGAME_API ATwoDCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATwoDCharacter();

protected:
    UPROPERTY(EditAnywhere, Category = "Movement")
        float MaxSpeed = 50;
    UPROPERTY(EditAnywhere, Category = "Movement")
        float StrafeSpeed = 5;
    UPROPERTY(BlueprintReadOnly, Category = "Movement")
        float Speed = 0;

    UPROPERTY(BlueprintReadOnly, Category = "Components")
        class UCameraComponent* Camera;
    UPROPERTY(BlueprintReadOnly, Category = "Components")
        class USpringArmComponent* CameraArm;
    UPROPERTY(BlueprintReadOnly, Category = "Components")
        class UPaperSprite* Sprite;

    class UFloatingPawnMovement* FloatingPawnMovement;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

  void Boost();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

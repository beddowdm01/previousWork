//Daniel Beddow, 20/10/2019. GameMode class header

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CPPGameMode.generated.h"

/**
 * 
 */
UCLASS()
class CPPGAME_API ACPPGameMode : public AGameModeBase
{
	GENERATED_BODY()
    
public:
    ACPPGameMode();
    bool SpaceshipDestroyed = false;//if the spaceship is destroyed
    void AddScore(int Score);//adds score that is passed
    int Score;//current score
};

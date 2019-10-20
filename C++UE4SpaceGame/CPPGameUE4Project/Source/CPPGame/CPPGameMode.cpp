//Daniel Beddow, 20/10/2019. Game mode class file

#include "CPPGameMode.h"
#include "Spaceship.h"
#include "UObject/ConstructorHelpers.h"
#include "CPPGameState.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Spaceship.h"
#include "Kismet/GameplayStatics.h"


ACPPGameMode::ACPPGameMode()
{
    //finds the player class.
    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/SpaceshipBP"));
    if (PlayerPawnBPClass.Class != NULL)//if it exists
    {
        DefaultPawnClass = PlayerPawnBPClass.Class;//sets the deault pawn
    }
}

void ACPPGameMode::AddScore(int Score)
{
    if (ACPPGameState* GS = Cast<ACPPGameState>(GameState))//casts the gamestate
    {
        if (!SpaceshipDestroyed) //if the spaceship is not destroyed
        {
                GS->Score += Score;//add score.
        }

    }
}

//Daniel Beddow, 20/10/2019. Gamestate class header

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "CPPGameState.generated.h"

/**
 * 
 */
UCLASS()
class CPPGAME_API ACPPGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
    ACPPGameState();
    //Creates uproperty under the category stats
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    int32 Score;
};

//Daniel Beddow, 20/10/2019. GameHUD class header file.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CPPGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class CPPGAME_API ACPPGameHUD : public AHUD
{
	GENERATED_BODY()
	
public:

    ACPPGameHUD();
    virtual void BeginPlay() override;
    //Creates uproperty widgets category
    UPROPERTY(EditAnywhere, Category = "Widgets")
    TSubclassOf<class UUserWidget> ScoreClass;
    class UUserWidget* Score;

    UPROPERTY(EditAnywhere, Category = "Widgets")
    TSubclassOf<class UUserWidget> DiedClass;
    class UUserWidget* Died;

    void GameOver();//Ends the game

};

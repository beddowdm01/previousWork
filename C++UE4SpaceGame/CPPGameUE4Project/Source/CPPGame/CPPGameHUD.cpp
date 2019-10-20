//Daniel Beddow, 20/10/2019. GameHUD class that displays widgets.


#include "CPPGameHUD.h"
#include "UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Blueprint/UserWidget.h"
#include "Components/Widget.h"
#include "CPPWidget.h"
#include "UserWidget.h"

ACPPGameHUD::ACPPGameHUD()
{
}

void ACPPGameHUD::BeginPlay()
{
    Super::BeginPlay();
    if (ScoreClass)//If the scoreclass widget class exists
    {  
        Score = CreateWidget<UUserWidget>(GetGameInstance(), ScoreClass);//creates a widget from ther class
        if (Score)//if the score exists
        {
            Score->AddToViewport();//add it to the screen
        }
    }
}

void ACPPGameHUD::GameOver()
{
    if (Score)//remove the score widget
    {
        Score->RemoveFromViewport();
    }
    if (DiedClass)//if the died class exists
    {
        Died = CreateWidget<UUserWidget>(GetGameInstance(), DiedClass);//create the widget
        if (Died)
        {
            APlayerController* PC = GetOwningPlayerController();//set the player controller
            PC->bShowMouseCursor = true;//allow use of the mouse
            PC->bEnableClickEvents = true;
            PC->bEnableMouseOverEvents = true;
            Died->AddToViewport();//add the widget to the viewport
        }
    }
}

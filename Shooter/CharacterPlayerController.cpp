// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterPlayerController.h"
#include "Blueprint/UserWidget.h"


void ACharacterPlayerController::BeginPlay()
{
    Super::BeginPlay();

    HUD = CreateWidget(this, Crossair);
    if (HUD != nullptr)
    {
        HUD->AddToViewport();

    }
    
    
}

void ACharacterPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
    Super::GameHasEnded(EndGameFocus,bIsWinner);

    HUD->RemoveFromViewport();

    if (bIsWinner)
    {
      UUserWidget* WinerScreenClass = CreateWidget(this,WinScreen);
      
      if (WinerScreenClass != nullptr)
      {
         WinerScreenClass->AddToViewport();
      }
      
    }
    else{
        UUserWidget* LoseScreenClass = CreateWidget(this,LoseScreen);

        if (LoseScreenClass != nullptr){

            LoseScreenClass->AddToViewport();
        }
        
    }
    

    

    GetWorldTimerManager().SetTimer(RestartTimer,this,&APlayerController::RestartLevel, RestartDelay);
}



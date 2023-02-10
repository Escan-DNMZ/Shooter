// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterAiController.h"
#include "ShooterCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "SG_SaveGame.h"




void AKillEmAllGameMode::BeginPlay()
{
    Super::BeginPlay();

    USG_SaveGame* LoadGame = Cast<USG_SaveGame>(UGameplayStatics::LoadGameFromSlot("SG",0));

    if(LoadGame){
        GScore = LoadGame->Score;
    }

   

   
 
}

int AKillEmAllGameMode::Scored()
{
   

	return GScore; 
}


void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled)
{
    Super::PawnKilled(PawnKilled);

    GScore += NewScore;

    APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
    if (PlayerController != nullptr)
    {
     
       EndGame(false);
    }
    
  
    for (AShooterAiController* AiController : TActorRange<AShooterAiController>(GetWorld()))
    {
        
        if (AiController->IsDead() == false)
        {
            
            
            return;
        }
        
    }
    
    EndGame(true);
    
   
    
   
    
}

void AKillEmAllGameMode::EndGame(bool bIsPlayerWinner)
{
    for (AController* Controller : TActorRange<AController>(GetWorld())){
        bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
         Controller->GameHasEnded(Controller->GetPawn(),bIsWinner);
       
       
       USG_SaveGame* SaveGame = Cast<USG_SaveGame>(UGameplayStatics::CreateSaveGameObject(USG_SaveGame::StaticClass()));

        if (SaveGame)
        {
            SaveGame->Score = GScore;

            UGameplayStatics::SaveGameToSlot(SaveGame,"SG",0);
        }
     
    }
     
}



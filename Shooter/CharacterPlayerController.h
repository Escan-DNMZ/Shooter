// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CharacterPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API ACharacterPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;	

public:
	virtual void GameHasEnded(AActor* EndGameFocus, bool bIsWinner) override;

	
private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> LoseScreen;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> WinScreen;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> Crossair;

	UPROPERTY()
	UUserWidget* HUD;

	UPROPERTY(EditAnywhere)
		float RestartDelay = 5;

		FTimerHandle RestartTimer;
};

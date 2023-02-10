// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShooterGameModeBase.h"
#include "KillEmAllGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API AKillEmAllGameMode : public AShooterGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	virtual void PawnKilled(APawn* PawnKilled) override;

	UFUNCTION(BlueprintPure)
	int Scored();

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	int GScore = 0;

	UPROPERTY(EditAnywhere)
	int NewScore = 5;
	
	
	
private:
	void EndGame(bool bIsPlayerWinner);

};

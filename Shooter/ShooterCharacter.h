// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InteractInterface.h"
#include "ShooterCharacter.generated.h"

class AGun;

UCLASS()
class SHOOTER_API AShooterCharacter : public ACharacter, public IInteractInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

	

	virtual void Interact() override;

protected:
	virtual void BeginPlay() override;

	
	

public:	

	

	UFUNCTION(BlueprintPure)
	bool IsDead() const;

	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const;

	// Called every fram
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	void Shoot();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		TArray<AGun*> weapons;

	void SwitchNextPrimaryWeapon();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int weaponIdex;

	
private:
	void MoveForward(float AxisValue);


	void MoveRight(float AxisValue);

	void LookUpRate(float AxisValue);

	void LookRightRate(float AxisValue);



	UPROPERTY(VisibleAnywhere)
	float Health;

	

	
	UPROPERTY(EditAnywhere)
	float TurnRate = 70.f;

	UPROPERTY(EditAnywhere)
	float RightRate = 80.f;

	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 100;

	UPROPERTY(EditDefaultsOnly)
	float NewHealth = 10;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> GunClass;

	

	UPROPERTY()
	AGun* Gun;
};


// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class SHOOTER_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

	void PullTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent, Category = "HUD")
		void SwitchWeaponMesh(int _index);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMeshComponent* Mesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UParticleSystem* MuzzleFlash;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UParticleSystem* Flash;



	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Damage = 10;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USoundBase* MuzzleSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USoundBase* ImpactSound;

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	

	


	UPROPERTY(EditAnywhere)
	float MaxRange = 1000;


	bool GunTrace(FHitResult& Hit, FVector& ShotDirection);


	AController* GetOwnerController() const;
};

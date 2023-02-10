// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "Gun.h"
#include "Components/CapsuleComponent.h"
#include "ShooterGameModeBase.h"
#include "Components/MeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "KillEmAllGameMode.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"



// Sets default values
AShooterCharacter::AShooterCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	
}


// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	Gun = GetWorld()->SpawnActor<AGun>(GunClass);
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	Gun->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform,TEXT("WeaponSocket"));
	Gun->SetOwner(this);



	weaponIdex = 0;

}



bool AShooterCharacter::IsDead() const
{
  	
	
	return Health <= 0;
		
}

float AShooterCharacter::GetHealthPercent() const
{
	return Health / MaxHealth;
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AShooterCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookRight"),this,&APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("LookRightRate"),this,&APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"),this,&AShooterCharacter::LookUpRate);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed , this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Shot"),EInputEvent::IE_Pressed, this, &AShooterCharacter::Shoot);
	PlayerInputComponent->BindAction(TEXT("Switch"),EInputEvent::IE_Pressed, this, &AShooterCharacter::SwitchNextPrimaryWeapon);

}


void AShooterCharacter::SwitchNextPrimaryWeapon() {
	switch (weaponIdex)
	{
	case 0:
		if (weapons.Num() > 0)
		{
			weaponIdex = 0;
			Gun->SwitchWeaponMesh(weaponIdex);
		}
		else 
		{
			weaponIdex = 0;
			Gun->SwitchWeaponMesh(weaponIdex);
		}
		break;
	case 1:
		if (weapons.Num() > 1)
		{
			weaponIdex = 1;
			Gun->SwitchWeaponMesh(weaponIdex);
		}
		else
		{
			weaponIdex = 0;
			Gun->SwitchWeaponMesh(weaponIdex);
		}
		break;

	default:
		break;
	}
}

float AShooterCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float DamageApplied = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageApplied = FMath::Min(Health,DamageApplied);
	Health -= DamageApplied; 

	if (IsDead())
	{
		AShooterGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AShooterGameModeBase>();
		if(GameMode != nullptr){
			GameMode->PawnKilled(this);
		}
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		
	}
	

	return DamageApplied;
}

void AShooterCharacter::MoveForward(float AxisValue){
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AShooterCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void AShooterCharacter::LookUpRate(float AxisValue){
	AddControllerPitchInput(AxisValue * TurnRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::LookRightRate(float AxisValue)
{
	AddControllerYawInput(AxisValue * RightRate * GetWorld()->GetDeltaSeconds());
}




void AShooterCharacter::Shoot()
{
	Gun->PullTrigger();
}

void AShooterCharacter::Interact()
{
	Health += NewHealth;
}
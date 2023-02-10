// Fill out your copyright notice in the Description page of Project Settings.


#include "AL_AnimInstance.h"
#include "ShooterCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UAL_AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);
    if (TryGetPawnOwner())
    {
      
        bSpeed = TryGetPawnOwner()->GetVelocity().Size();
        
         
        FVector InverseTransformDirection = TryGetPawnOwner()->GetActorTransform().InverseTransformVectorNoScale(TryGetPawnOwner()->GetVelocity());
        AnglVlu = FRotationMatrix::MakeFromX(InverseTransformDirection).Rotator().Yaw;

        AShooterCharacter* Shooter = Cast<AShooterCharacter>(TryGetPawnOwner());
        if(Shooter){
            bIsDead = Shooter->IsDead(); 
        }

         ACharacter* Character = Cast<ACharacter>(TryGetPawnOwner());
         if (Character)
         {
            bIsAirborne =  Character->GetCharacterMovement()->IsFalling();
         }
         
    }
    
}

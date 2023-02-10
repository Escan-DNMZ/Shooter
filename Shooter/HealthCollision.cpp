// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthCollision.h"
#include "InteractInterface.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AHealthCollision::AHealthCollision()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	BoxCollision->SetupAttachment(GetRootComponent());

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(BoxCollision);

}

// Called when the game starts or when spawned
void AHealthCollision::BeginPlay()
{
	Super::BeginPlay();

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AHealthCollision::BeginOverlap);
	
}

// Called every frame
void AHealthCollision::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHealthCollision::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	IInteractInterface* Interface = Cast<IInteractInterface>(OtherActor);

	if (Interface)
	{
		Interface->Interact();
		UGameplayStatics::SpawnSoundAttached(HealthSound, Mesh,TEXT("Health Sound"));
		AActor::Destroy();
	}
	
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatingActor.h"

// Sets default values
AFloatingActor::AFloatingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CustomStaticMesh"));

	// Typically we initialize things in the constructor

	InitialLocation = FVector(0.0f);
	PlacedLocation = FVector(0.0f);
	WorldOrigin = FVector(0.0f, 0.0f, 0.0f);
	InitialDirection = FVector(0.0f, 0.0f, 0.0f);

	bInitializeFloatingActorLocations = false;
	bCanFloat = false;
	

}

// Called when the game starts or when spawned
void AFloatingActor::BeginPlay()
{
	Super::BeginPlay();

	PlacedLocation = GetActorLocation();

	if (bInitializeFloatingActorLocations)
	{
		SetActorLocation(InitialLocation);
	}
	
	
}

// Called every frame
void AFloatingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bCanFloat) 
	{
		FHitResult HitResult;
		AddActorLocalOffset(InitialDirection, false, &HitResult);
		// AddActorLocalRotation(FRotator(1.0f, 1.0f, 1.0f), false, &HitResult); it will rotate the actor
		
	}

}


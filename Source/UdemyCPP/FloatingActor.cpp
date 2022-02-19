// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatingActor.h"
#include "Components/StaticMeshComponent.h"

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
	InitialForce = FVector(6000000.f, 0.0f, 0.0f);
	InitialTorque = FVector(6000000.f, 0.0f, 0.0f);

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

	
	StaticMesh->AddForce(InitialForce);
	StaticMesh->AddTorqueInRadians(InitialTorque);
	

	FRotator Rotation = FRotator(0.0f, 0.0f, 0.0f);

	//AddActorLocalOffset(LocalOffset, true, &HitResult);
	AddActorLocalRotation(Rotation);

	
	
	
}

// Called every frame
void AFloatingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



	if (bCanFloat) 
	{
		FHitResult HitResult;
		AddActorLocalOffset(InitialDirection, true, &HitResult);
		// AddActorLocalRotation(FRotator(1.0f, 1.0f, 1.0f), false, &HitResult); it will rotate the actor

		FVector HitLocation = HitResult.Location;
		
		// Simple example of how to get an information from the hit result
		// UE_LOG(LogTemp, Warning, TEXT("Hit Location: X = %f, Y = %f, Z = %f"), HitLocation.X, HitLocation.Y, HitLocation.Z);

		// if Sweeping is enabled, we can collide with an object even simulate physics is off

		//FRotator Rotation = FRotator(0.0f, 1.0f, 0.0f);
		//AddActorLocalRotation(Rotation);
	}

}


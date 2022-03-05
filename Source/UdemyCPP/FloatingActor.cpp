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

	RunningTime = 0.f;

	A = 0.f;
	B = 0.f;
	C = 0.f;
	D = 0.f;
	

}

// Called when the game starts or when spawned
void AFloatingActor::BeginPlay()
{
	Super::BeginPlay();

	float InitialX = FMath::FRandRange(-500.f, 500.f);
	float InitialY = FMath::FRandRange(-500.f, 500.f);
	float InitialZ = FMath::FRandRange(0.f, 500.f);

	InitialLocation.X = InitialX;
	InitialLocation.Y = InitialY;
	InitialLocation.Z = InitialZ;

	//InitialLocation *= 20.f; // It will return a random number between 0 and 20. Initial FRand Func returns number between 0 and 1. We dont need it in FRandRange

	PlacedLocation = GetActorLocation();

	if (bInitializeFloatingActorLocations)
	{
		SetActorLocation(InitialLocation);
	}

	BaseZLocation = PlacedLocation.Z;

	
	//StaticMesh->AddForce(InitialForce);
	//StaticMesh->AddTorqueInRadians(InitialTorque);
	

	//FRotator Rotation = FRotator(0.0f, 0.0f, 0.0f);

	//AddActoLocalOffset(LocalOffset, true, &HitResult);
	//AddActorLocalRotation(Rotation);

	
	
	
}

// Called every frame
void AFloatingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



	if (bCanFloat) 
	{
		/*FHitResult HitResult;
		AddActorLocalOffset(InitialDirection, true, &HitResult);
		 AddActorLocalRotation(FRotator(1.0f, 1.0f, 1.0f), false, &HitResult); it will rotate the actor

		FVector HitLocation = HitResult.Location;
		
		 Simple example of how to get an information from the hit result
		 UE_LOG(LogTemp, Warning, TEXT("Hit Location: X = %f, Y = %f, Z = %f"), HitLocation.X, HitLocation.Y, HitLocation.Z);

		if Sweeping is enabled, we can collide with an object even simulate physics is off

		FRotator Rotation = FRotator(0.0f, 1.0f, 0.0f);
		AddActorLocalRotation(Rotation);*/


		//-----------------------------------------------------------------------------------------------------//

		// Using Sine Function //

		FVector NewLocation = GetActorLocation();

		NewLocation.Z = BaseZLocation + A *  FMath::Sin(B * RunningTime - C) + D; 
		SetActorLocation(NewLocation);
		RunningTime += DeltaTime;
		
	}

}


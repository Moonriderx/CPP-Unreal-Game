// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloatingActor.generated.h"

UCLASS() // it inherit the "blueprintable" from AActor
class UDEMYCPP_API AFloatingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloatingActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ActorMeshComponents")
	UStaticMeshComponent* StaticMesh; // Creating a POINTER to UStaticMeshComponent variable (that does not mean we've created the actual component)

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "FloatingActor Variables") // EditInstanceOnly means that the particular "InitialLocation" is editable only on an instance of a FloatingActor
		// its only editable on the instance, not on the default BP
	FVector InitialLocation;

	// Location of the actor when dragged in from the editor
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "FloatingActor Variables")
	FVector PlacedLocation;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "FloatingActor Variables")
	FVector WorldOrigin;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FloatingActor Variables") // EditAnywhere gives us to edit the variable anywhere. In the BP, in the instance etc..
	FVector InitialDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FloatingActor Variables") //EditDefaultsOnly it allows us to modify the variable in the default BP
	bool bInitializeFloatingActorLocations;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FloatingActor Variables")
	bool bCanFloat;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

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

	UPROPERTY(VisibleAnywhere, Category = "ActorMeshComponents")
	UStaticMeshComponent* StaticMesh; // Creating a POINTER to UStaticMeshComponent variable (that does not mean we've created the actual component)

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "FloatingActor Vectors") // EditInstanceOnly means that the particular "InitialLocation" is editable only on an instance of a FloatingActor
		// its only editable on the instance, not on the default BP
	FVector InitialLocation = FVector(0.0f, 0.0f, 180.0f);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

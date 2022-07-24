// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CustomCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class UDEMYCPP_API UCustomCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	
protected:

private:

	UPROPERTY(Category = "Character Movement : Climbing", EditAnywhere, meta = (ClampMin = "1.0", ClampMax = "75.0"))
	float MinHorizontalDegreesToStartClimbing = 25.f; // Control minimum Angle
	
	TArray<FHitResult> CurrentWallHits;

	UPROPERTY(Category = "Character Movement : Climbing", EditAnywhere)
	int CollisionCapsuleRadius = 50;

	UPROPERTY(Category = "Character Movement : Climbing", EditAnywhere)
	int CollisionCapsuleHalfHeight = 72;

	FCollisionQueryParams ClimbQueryParams;

private:

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SweepAndStoreWallHits();

	bool CanStartClimbing();


};

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
	UFUNCTION(BlueprintPure)
	bool IsClimbing() const; /*check if the movement component mode is Custom, 
							 and if the custom mode is Climbing we need a function to retrieve the climbing surface normal*/ 

	UFUNCTION(BlueprintPure)
	FVector GetClimbSurfaceNormal() const;

	void TryClimbing(); // function that will enable climbing

	void CancelClimbing(); // function that exits climbing
	
protected:

private:

	UPROPERTY(Category = "Character Movement : Climbing", EditAnywhere, meta = (ClampMin = "1.0", ClampMax = "75.0"))
	float MinHorizontalDegreesToStartClimbing = 25.f; // Control minimum Angle

	UPROPERTY(Category = "Character Movement : Climbing", EditAnywhere, meta = (ClampMin = "10.0", ClampMax = "500.0"))
	float MaxClimbingSpeed = 120.f;

	UPROPERTY(Category = "Character Movement : Climbing", EditAnywhere, meta=(ClampMin = "10.0", ClampMax = "2000.0"))
	float MaxClimbAcceleration = 380.f;

	UPROPERTY(Category = "Character Movement : Climbing", EditAnywhere, meta=(ClampMin = "0.0", ClampMax = "3000.0"))
	float BrakingDecelerationClimbing = 550.f;

	UPROPERTY(Category = "Character Movement : Climbing", EditAnywhere, meta = (ClampMin = "0.0", ClampMax = "60.0"))
	int ClimbingRotationSpeed = 6;

	UPROPERTY(Category = "Character Movement : Climbing", EditAnywhere, meta = (ClampMin = "0.0", ClampMax = "60.0"))
	float ClimbingSnapSpeed = 4.f;

	UPROPERTY(Category = "Character Movement : Climbing", EditAnywhere, meta = (ClampMin = "0.0", ClampMax = "80.0"))
	float DistanceFromSurface = 45.f;
	
	TArray<FHitResult> CurrentWallHits;

	UPROPERTY(Category = "Character Movement : Climbing", EditAnywhere)
	int CollisionCapsuleRadius = 50;

	UPROPERTY(Category = "Character Movement : Climbing", EditAnywhere)
	int CollisionCapsuleHalfHeight = 72;

	UPROPERTY(Category = "Character Movement Climbing", EditAnywhere, meta = (ClampMin = "0.0", ClampMax = "80.0"))
	float ClimbingCollisionShrinkAmount = 30;

	FCollisionQueryParams ClimbQueryParams;

	bool bWantsToClimb = false;

	FVector CurrentClimbingNormal;
	FVector CurrentClimbingPosition;

private:

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void OnMovementUpdated(float DeltaSeconds, const FVector& OldLocation, const FVector& OldVelocity) override;

	virtual void PhysCustom(float deltaTime, int32 Iterations) override;

	virtual void OnMovementModeChanged(EMovementMode PreviousMovementMode, uint8 PreviousCustomMode) override;

	virtual float GetMaxSpeed() const override;

	virtual float GetMaxAcceleration() const override;

	void PhysClimbing(float deltaTime, int32 Iterations);

	void SweepAndStoreWallHits();

	void ComputeSurfaceInfo();

	void ComputeClimbingVelocity(float deltaTime);

	void StopClimbing(float deltaTime, int32 Iterations);

	void MoveAlongClimbingSurface(float deltaTime);

	void SnapToClimbingSurface(float deltaTime) const;

	bool CanStartClimbing();

	bool EyeHeightTrace(const float TraceDistance) const;

	bool IsFacingSurface(float Steepness) const;

	bool ShouldStopClimbing() const;

	FQuat GetClimbingRotation(float deltaTime) const;



	


};

// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomCharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "CustomEnums.h"
#include "Components/CapsuleComponent.h"

void UCustomCharacterMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	ClimbQueryParams.AddIgnoredActor(GetOwner());
}

void UCustomCharacterMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	SweepAndStoreWallHits();

}

void UCustomCharacterMovementComponent::OnMovementUpdated(float DeltaSeconds, const FVector& OldLocation, const FVector& OldVelocity)
{

	if (bWantsToClimb)
	{
		SetMovementMode(EMovementMode::MOVE_Custom, ECustomMovementMode::CMOVE_Climbing);
	}
	
	Super::OnMovementUpdated(DeltaSeconds, OldLocation, OldVelocity);

}

void UCustomCharacterMovementComponent::SweepAndStoreWallHits() /* the job of this function is to call SweetMultiByChannel with appropriate params
 and store the hits it retrieves */
{
	const FCollisionShape CollisionShape = FCollisionShape::MakeCapsule(CollisionCapsuleRadius, CollisionCapsuleHalfHeight);

	const FVector StartOffSet = UpdatedComponent->GetForwardVector() * 20; // The UpdatedComponent is the component we move and update. We will use it throughout the project to retrieve information like the current location and rotation

	// Avoid using the same Start/End location for a Sweep, as it doesn't trigger hits on Landscapes

	const FVector Start = UpdatedComponent->GetComponentLocation() + StartOffSet;
	const FVector End = Start + UpdatedComponent->GetForwardVector();

	TArray<FHitResult> Hits;
	
	const bool HitWall = GetWorld()->SweepMultiByChannel(Hits, Start, End, FQuat::Identity, ECC_WorldStatic, CollisionShape, ClimbQueryParams);

	HitWall ? CurrentWallHits = Hits : CurrentWallHits.Reset();

}




bool UCustomCharacterMovementComponent::CanStartClimbing()
{
	for (FHitResult& Hit : CurrentWallHits) 
	{
	
		const FVector HorizontalNormal = Hit.Normal.GetSafeNormal2D();

		/*Finding the angle between character's forward vector and the horizontal project normal by calculating the Arcossine of the dot product*/

		const float HorizontalDot = FVector::DotProduct(UpdatedComponent->GetForwardVector(), -HorizontalNormal);
		const float VerticalDot = FVector::DotProduct(Hit.Normal, HorizontalNormal);

		const float HorizontalDegrees = FMath::RadiansToDegrees(FMath::Acos(HorizontalDot));

		const bool bIsCeiling = FMath::IsNearlyZero(VerticalDot);

		/* If the result is 0 this means vectors are perpendicular e.g flat ceilling */
		if (HorizontalDegrees <= MinHorizontalDegreesToStartClimbing && !bIsCeiling && IsFacingSurface(VerticalDot))
		{
			return true;
		}
	
	}


	return false;
}


/* Trace forward the character eye height. If hit something that means there is a surface where we can hang on and climb */

bool UCustomCharacterMovementComponent::EyeHeightTrace(const float TraceDistance) const 
{

	FHitResult UpperEdgeHit; 

	const FVector Start = UpdatedComponent->GetComponentLocation() + (UpdatedComponent->GetUpVector() * GetCharacterOwner()->BaseEyeHeight);

	const FVector End = Start + (UpdatedComponent->GetForwardVector() * TraceDistance);

	return GetWorld()->LineTraceSingleByChannel(UpperEdgeHit, Start, End, ECC_WorldStatic, ClimbQueryParams);
}

/* Determing how steep the surface is. Calculating the line trace and calling EyeHeightTrace */

bool UCustomCharacterMovementComponent::IsFacingSurface(const float Steepness) const
{
	constexpr float BaseLength = 80.f;

	const float SteepnessMultiplier = 1 + (1 - Steepness) * 5;


	return EyeHeightTrace(BaseLength * SteepnessMultiplier);
}

bool UCustomCharacterMovementComponent::ShouldStopClimbing() const
{
	const bool bIsOnCeiling = FVector::Parallel(CurrentClimbingNormal, FVector::UpVector);
	
	return !bWantsToClimb || CurrentClimbingNormal.IsZero() || bIsOnCeiling;
}

FQuat UCustomCharacterMovementComponent::GetClimbingRotation(float deltaTime) const
{
	const FQuat Current = UpdatedComponent->GetComponentQuat();
	const FQuat Target = FRotationMatrix::MakeFromX(-CurrentClimbingNormal).ToQuat();

	return FMath::QInterpTo(Current, Target, deltaTime, ClimbingRotationSpeed);
}


void UCustomCharacterMovementComponent::TryClimbing()
{

	if (CanStartClimbing())
	{
		bWantsToClimb = true;
	}

}

void UCustomCharacterMovementComponent::CancelClimbing()
{
	bWantsToClimb = false;
}

bool UCustomCharacterMovementComponent::IsClimbing() const
{
	return MovementMode == EMovementMode::MOVE_Custom && CustomMovementMode == ECustomMovementMode::CMOVE_Climbing; // set the modes
}

void UCustomCharacterMovementComponent::PhysCustom(float deltaTime, int32 Iterations)
{
	if (CustomMovementMode == ECustomMovementMode::CMOVE_Climbing)
	{
		PhysClimbing(deltaTime, Iterations);
	}
	Super::PhysCustom(deltaTime, Iterations);
}

void UCustomCharacterMovementComponent::OnMovementModeChanged(EMovementMode PreviousMovementMode, uint8 PreviousCustomMode)
{
	if (IsClimbing())
	{
		bOrientRotationToMovement = false;

		UCapsuleComponent* Capsule = CharacterOwner->GetCapsuleComponent();
		Capsule->SetCapsuleHalfHeight(Capsule->GetUnscaledCapsuleHalfHeight() - ClimbingCollisionShrinkAmount);
	}
	
	const bool bWasClimbing = PreviousMovementMode == MOVE_Custom && PreviousCustomMode == CMOVE_Climbing;
	if (bWasClimbing)
	{
		bOrientRotationToMovement = true;

		const FRotator StandRotation = FRotator(0, UpdatedComponent->GetComponentRotation().Yaw, 0);
		UpdatedComponent->SetRelativeRotation(StandRotation);

		UCapsuleComponent* Capsule = CharacterOwner->GetCapsuleComponent();
		Capsule->SetCapsuleHalfHeight(Capsule->GetUnscaledCapsuleHalfHeight() + ClimbingCollisionShrinkAmount);

		// Reset Velocity & Acceleration after exiting climbing mode

		StopMovementImmediately();
	}

	Super::OnMovementModeChanged(PreviousMovementMode, PreviousCustomMode);


}

float UCustomCharacterMovementComponent::GetMaxSpeed() const
{
	return IsClimbing() ? MaxClimbingSpeed : Super::GetMaxSpeed();
}

float UCustomCharacterMovementComponent::GetMaxAcceleration() const
{
	return IsClimbing() ? MaxClimbAcceleration : Super::GetMaxAcceleration();
}

void UCustomCharacterMovementComponent::PhysClimbing(float deltaTime, int32 Iterations)
{

	if (deltaTime < MIN_TICK_TIME)
	{
		return;
	}

	ComputeSurfaceInfo();

	if (ShouldStopClimbing())
	{
		StopClimbing(deltaTime, Iterations);
		return;
	}

	ComputeClimbingVelocity(deltaTime);

	const FVector OldLocation = UpdatedComponent->GetComponentLocation();

	MoveAlongClimbingSurface(deltaTime);

	if (!HasAnimRootMotion() && !CurrentRootMotion.HasOverrideVelocity())
	{
		Velocity = (UpdatedComponent->GetComponentLocation() - OldLocation / deltaTime);
	}

	SnapToClimbingSurface(deltaTime);

}

FVector UCustomCharacterMovementComponent::GetClimbSurfaceNormal() const
{
	return CurrentClimbingNormal;
}

void UCustomCharacterMovementComponent::ComputeClimbingVelocity(float deltaTime)
{

	RestorePreAdditiveRootMotionVelocity();

	if (!HasAnimRootMotion() && !CurrentRootMotion.HasOverrideVelocity())
	{
		constexpr float Friction = 0.0f;
		constexpr bool bFluid = false;
		CalcVelocity(deltaTime, Friction, bFluid, BrakingDecelerationClimbing);
	}
	
	ApplyRootMotionToVelocity(deltaTime);

}

void UCustomCharacterMovementComponent::StopClimbing(float deltaTime, int32 Iterations)
{

	bWantsToClimb = false;
	SetMovementMode(EMovementMode::MOVE_Falling);
	StartNewPhysics(deltaTime, Iterations);

}

void UCustomCharacterMovementComponent::MoveAlongClimbingSurface(float deltaTime)
{

	const FVector Adjusted = Velocity * deltaTime;

	FHitResult Hit(1.f);

	SafeMoveUpdatedComponent(Adjusted, GetClimbingRotation(deltaTime), true, Hit);

	if (Hit.Time < 1.f)
	{
		HandleImpact(Hit, deltaTime, Adjusted);
		SlideAlongSurface(Adjusted, (1.f - Hit.Time), Hit.Normal, Hit, true);
	}
}

void UCustomCharacterMovementComponent::SnapToClimbingSurface(float deltaTime) const
{


	const FVector Forward = UpdatedComponent->GetForwardVector();
	const FVector Location = UpdatedComponent->GetComponentLocation();
	const FQuat Rotation = UpdatedComponent->GetComponentQuat();

	const FVector ForwardDifference = (CurrentClimbingPosition - Location).ProjectOnTo(Forward);
	const FVector Offset = -CurrentClimbingNormal * (ForwardDifference.Length() - DistanceFromSurface);

	constexpr bool bSweep = true;
	UpdatedComponent->MoveComponent(Offset * ClimbingSnapSpeed * deltaTime, Rotation, bSweep);

}


void UCustomCharacterMovementComponent::ComputeSurfaceInfo()
{

	CurrentClimbingNormal = FVector::ZeroVector;
	CurrentClimbingPosition = FVector::ZeroVector;

	if (CurrentWallHits.IsEmpty())
	{
		return;
	}

	for (const FHitResult& WallHit : CurrentWallHits)
	{
		CurrentClimbingPosition += WallHit.ImpactPoint;
		CurrentClimbingNormal = WallHit.Normal;
	}

	CurrentClimbingPosition /= CurrentWallHits.Num();
	CurrentClimbingNormal = CurrentClimbingNormal.GetSafeNormal();

}

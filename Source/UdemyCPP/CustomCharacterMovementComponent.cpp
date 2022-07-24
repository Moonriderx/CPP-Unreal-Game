// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomCharacterMovementComponent.h"
#include "GameFramework/Character.h"



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
		if (HorizontalDegrees <= MinHorizontalDegreesToStartClimbing && !bIsCeiling)
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

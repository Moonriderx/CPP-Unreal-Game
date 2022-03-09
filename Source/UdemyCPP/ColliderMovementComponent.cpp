// Fill out your copyright notice in the Description page of Project Settings.


#include "ColliderMovementComponent.h"

void UColliderMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime)) // we are checking to see if the pawn owner is not null, if updateComponent is not null
	{
		return;
	}

	FVector DesiredMovementThisFrame = ConsumeInputVector().GetClampedToMaxSize(1.0f); // clamp the vector to have a magnitude of 1. (normalizing the vector)

	if (!DesiredMovementThisFrame.IsNearlyZero()) 
	{
		FHitResult Hit;

		SafeMoveUpdatedComponent(DesiredMovementThisFrame, UpdatedComponent->GetComponentRotation(), true, Hit);

		if (Hit.IsValidBlockingHit()) // returns if we hit something or not. If we bumb into something, slide along the side of it
		{
			SlideAlongSurface(DesiredMovementThisFrame, 1.f - Hit.Time, Hit.Normal, Hit);

			/*
			It takes the amount of movement we would like to move, it takes the amount of time since the time that we hit the surface, The normal 
			vector describes the orientation of the face that we hit, and it takes the hit result itself.

			It performs amount of calculation that will tell us where to move the pawn if we were to slide along the surface
			*/
		}
	}
}
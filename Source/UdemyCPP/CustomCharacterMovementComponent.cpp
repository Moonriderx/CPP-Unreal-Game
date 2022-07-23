// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomCharacterMovementComponent.h"

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

void UCustomCharacterMovementComponent::SweepAndStoreWallHits()
{
	const FCollisionShape CollisionShape = FCollisionShape::MakeCapsule(CollisionCapsuleRadius, CollisionCapsuleHalfHeight);

	const FVector StartOffSet = UpdatedComponent->GetForwardVector() * 20;

	// Avoid using the same Start/End location for a Sweep, as it doesn't trigger hits on Landscapes

	const FVector Start = UpdatedComponent->GetComponentLocation() + StartOffSet;
	const FVector End = Start + UpdatedComponent->GetForwardVector();

	TArray<FHitResult> Hits;
	const bool HitWall = GetWorld()->SweepMultiByChannel(Hits, Start, End, FQuat::Identity, ECC_WorldStatic, CollisionShape, ClimbQueryParams);

	HitWall ? CurrentWallHits = Hits : CurrentWallHits.Reset();

}

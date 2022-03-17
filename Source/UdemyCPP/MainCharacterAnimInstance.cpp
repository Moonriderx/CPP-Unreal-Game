// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacterAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"

void UMainCharacterAnimInstance::NativeInitializeAnimation()
{
	if (Pawn == nullptr) 
	{
		Pawn = TryGetPawnOwner();
	}


}

void UMainCharacterAnimInstance::UpdateAnimationProperties()
{
	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();
	}

	if (Pawn) 
	{
		FVector Speed = Pawn->GetVelocity(); // get the speed 
		FVector LateralSpeed = FVector(Speed.X, Speed.Y, 0.f); // zero out its Z component
		MovementSpeed = LateralSpeed.Size(); // get magnetude of that vector and set it to movement Speed

		bIsInAir = Pawn->GetMovementComponent()->IsFalling(); // check if is in air
	}

}
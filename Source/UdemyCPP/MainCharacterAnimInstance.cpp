// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacterAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MainCharacter.h"

void UMainCharacterAnimInstance::NativeInitializeAnimation()
{
	if (Pawn == nullptr) 
	{
		Pawn = TryGetPawnOwner();
		if (Pawn) 
		{
			MainCharacter = Cast<AMainCharacter>(Pawn); // cast pawn to a Main

		}
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

		if (MainCharacter == nullptr)
		{
			MainCharacter = Cast<AMainCharacter>(Pawn); // access to main straiht from BP
		}
	}

}
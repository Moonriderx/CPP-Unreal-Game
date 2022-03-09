// Fill out your copyright notice in the Description page of Project Settings.


/*

This component is only for educational purposes. Usually we let unreal built-in movement component to handle the logic and we build on top of it.



*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "ColliderMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class UDEMYCPP_API UColliderMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()
public:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	
};

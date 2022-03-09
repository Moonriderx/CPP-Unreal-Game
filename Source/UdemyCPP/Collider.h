// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Collider.generated.h"

UCLASS()
class UDEMYCPP_API ACollider : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACollider();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UPROPERTY(VisibleAnywhere, Category = "Mesh")
		class UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
		class USphereComponent* SphereComponent;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	    class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	    class USpringArmComponent* SpringArm; // control the camera's motion


	FORCEINLINE UStaticMeshComponent* GetMeshComponent() // it makes the function inline
	{
		return MeshComponent;
	}

	FORCEINLINE void SetMeshComponent(UStaticMeshComponent* Mesh)
	{
		MeshComponent = Mesh;
	}


	FORCEINLINE USphereComponent* GetSphereComponent() // it makes the function inline
	{
		return SphereComponent;
	}

	FORCEINLINE void SetSphereComponent(USphereComponent* Sphere)
	{
		SphereComponent = Sphere;
	}




	FORCEINLINE UCameraComponent* GetCameraComponent() // it makes the function inline
	{
		return Camera;
	}

	FORCEINLINE void SetCameraComponent(UCameraComponent* InCamera)
	{
		Camera = InCamera;
	}


	FORCEINLINE USpringArmComponent* GetSpringArmComponent() // it makes the function inline
	{
		return SpringArm;
	}

	FORCEINLINE void SetSpringArmComponent(USpringArmComponent* InSpringArm)
	{
		SpringArm = InSpringArm;
	}



private:

	void MoveForward(float input);
	void MoveRight(float input);
};

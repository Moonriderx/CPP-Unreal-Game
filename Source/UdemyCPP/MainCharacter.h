// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

/** Movement Status Enum */

UENUM(BlueprintType)
enum class EMovementStatus : uint8
{
	EMS_Normal UMETA(DisplayName = "Normal"),
	EMS_Sprinting UMETA(DisplayName = "Sprinting"),
	EMS_ExhaustedWalking UMETA(DisplayName = "ExhaustedWalking"),

	EMS_MAX UMETA(DisplayName = "DefaultMAX")
};

/** Stamina Status Enum */

UENUM(BlueprintType)
enum class EStaminaStatus : uint8 
{
	ESS_Normal UMETA(DisplayName = "Normal"),
	ESS_BelowMinimum UMETA(DisplayName = "BelowMinimum"),
	ESS_Exhausted UMETA(DisplayName = "Exhausted"),
	ESS_ExhaustedRecovering UMETA(DisplayName = "ExhaustedRecovering"),

	ESS_MAX UMETA(DisplayName = "DefaultMax")

};

UCLASS()
class UDEMYCPP_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// We also need to make sure the Character class uses our newly created component instead of the base one.
	AMainCharacter(const FObjectInitializer& ObjectInitializer);

	/** the ACharacter still holds a reference to the UCharacterMovementComponent base type. 
	Consequently, we would need to cast it every time we use it. It’s a good idea to cache the cast and retrieve it with a function:
	*/

	UFUNCTION(BlueprintPure)
	FORCEINLINE UCustomCharacterMovementComponent* GetCustomCharacterMovement() const { return MovementComponent; }

	// FTimerHandle used for the delay
	UPROPERTY()
	FTimerHandle DashDelay;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Enums")
	EMovementStatus MovementStatus;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Enums")
	EStaminaStatus StaminaStatus;

	FORCEINLINE void SetStaminaStatus(EStaminaStatus Status) { StaminaStatus = Status; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float StaminaDrainRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MinSprintStamina;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Running")
	float RunningSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sprinting")
	float SprintingSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sprinting")
	float ExhaustedSpeed;

	bool bShiftKeyDown;

	bool bCanDash;

	/** Dash Montage */

	UPROPERTY(EditAnywhere)
	UAnimMontage* DashMontage;

	/** Camera boom positioning the camera behind the player */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow Camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera; 

	/** Base turn rate to scale turning functions for the camera */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

	/***
	/*
	/*
	Player Stats
	/*
	*/

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Stats")
	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Stats")
	float Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Stats")
	float MaxStamina;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Stats")
	float Stamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
	int32 Coins;



	void DecrementHealth(float Amount);

	void Die();

	void IncrementCoins(int32 Amount);

	/** Press down to enable sprinting */
	void ShiftKeyDown();

	/** Release down to disable sprinting */
	void ShiftKeyUp();

	/** Set movement status and running speed */
	void SetMovementStatus(EMovementStatus Status);

protected:

	void Dashing();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dashing")
	float DashDistance;

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly)
	UCustomCharacterMovementComponent* MovementComponent;
	

protected:
	// Called when the game starts or when spawned
	 virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Called for forwards/backwards input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** Called via Input to turn at a given rate 
	* @param Rate this is a normalized rate, i.e 1.0 means 100% of desired turn rate
	*/
	void TurnAtRate(float Rate);

	/** Called via Input to look up/down at a given rate
	* @param Rate this is a normalized rate, i.e 1.0 means 100% of desired look up/down rate
	*/
	void LookUpAtRate(float Rate);

	bool bLMBDown;
	void LMBDown();
	void LMBUp();
	void ResetDash();

	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Items");
	class AWeapon* EquippedWeapon;

	void SetEquippedWeapon(AWeapon* WeaponToSet);

	FORCEINLINE AWeapon* GetEquippedWeapon() { return EquippedWeapon; } // setter

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Items");
	class AItem* ActiveOverlappingItem;

	FORCEINLINE void SetActiveOverlappingItem(AItem* Item) { ActiveOverlappingItem = Item; } // setter


};

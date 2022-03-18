// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloorSwitch.generated.h"

UCLASS()
class UDEMYCPP_API AFloorSwitch : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloorSwitch();
	
	/** Overlap Volume for functionality to be triggered */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,  Category = "Floor Switch")
	class UBoxComponent* TriggerBox;

	/** Switch for the character to step on */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Floor Switch")
	class UStaticMeshComponent* FloorSwitch;

	/** Door to move when the floorSwitch is stepped on */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Floor Switch")
	UStaticMeshComponent* DoorMesh;
	
	/** Initial Location for the Door */
	UPROPERTY(BlueprintReadWrite, Category = "Floor Switch")
	FVector InitialDoorLocation;

	/** Initial Location for the Floor Switch */
	UPROPERTY(BlueprintReadWrite, Category = "Floor Switch")
	FVector InitialSwitchLocation;

	FTimerHandle SwitchHandle;

	void CloseDoor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Floor Switch")
	float SwitchTime;

	bool bCharacterOnSwitch;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UFUNCTION() // when we bind events to OnComponentBeginOverlap that function MUST be an UFUNCTION
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintImplementableEvent, Category = "Floor Switch") // make the function play a role as event. No need to implement in CPP, can do directly in BP's
	void RaiseDoor(); 

	UFUNCTION(BlueprintImplementableEvent, Category = "Floor Switch") // make the function play a role as event. No need to implement in CPP, can do directly in BP's
	void LowerDoor();

	UFUNCTION(BlueprintImplementableEvent, Category = "Floor Switch") // make the function play a role as event. No need to implement in CPP, can do directly in BP's
	void RaiseFloorSwitch();

	UFUNCTION(BlueprintImplementableEvent, Category = "Floor Switch") // make the function play a role as event. No need to implement in CPP, can do directly in BP's
    void LowerFloorSwitch();

	UFUNCTION(BlueprintCallable, Category = "Floor Switch") // we will call this function from BP, but the functionality will be scripted c++
	void UpdateDoorLocation(float Z);

	UFUNCTION(BlueprintCallable, Category = "Floor Switch") // we will call this function from BP, but the functionality will be scripted c++
	void UpdateFloorSwitchLocation(float Z);
};
 

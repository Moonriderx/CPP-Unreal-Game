// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "MainCharacter.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"
#include "particles/ParticleSystemComponent.h"

AWeapon::AWeapon() 
{
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh"));
	SkeletalMesh->SetupAttachment(GetRootComponent());

	bWeaponParticle = false;

	WeaponState = EWeaponState::EWS_Pickup;
}

void AWeapon::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	if (WeaponState == EWeaponState::EWS_Pickup && OtherActor)
	{
		AMainCharacter* MainCharacter = Cast<AMainCharacter>(OtherActor);
		if (MainCharacter)
		{
			//Equip(MainCharacter);
			MainCharacter->SetActiveOverlappingItem(this);
		}

	}
}

void AWeapon::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnOverlapEnd(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
	AMainCharacter* MainCharacter = Cast<AMainCharacter>(OtherActor);
	if (MainCharacter)
	{
		//Equip(MainCharacter);
		MainCharacter->SetActiveOverlappingItem(nullptr); // if we overlap and then step away the activeoverlappingmtei is null
	}

}

void AWeapon::Equip(AMainCharacter* Char)
{
	if (Char) // if character is valid
	{
		SkeletalMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore); // the camera will not collide with the sword
		SkeletalMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore); // the camera will not collide with the sword
		
		SkeletalMesh->SetSimulatePhysics(false); // set physics to false on the weapon

		const USkeletalMeshSocket* RightHandSocket = Char->GetMesh()->GetSocketByName("RightHandSocket"); 

		if (RightHandSocket)
		{
			RightHandSocket->AttachActor(this, Char->GetMesh()); // attach the actor to the skeleton
			bRotate = false;
			Char->SetEquippedItem(this);
			Char->SetActiveOverlappingItem(nullptr); // as soon as we've equip the item
		    
		}

		if (OnEquipSound) UGameplayStatics::PlaySound2D(this, OnEquipSound);

		if (!bWeaponParticle)
		{
			IdleParticlesComponent->Deactivate(); 
		    
		}

	}
}

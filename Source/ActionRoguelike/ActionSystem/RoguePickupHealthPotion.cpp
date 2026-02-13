// Fill out your copyright notice in the Description page of Project Settings.


#include "RoguePickupHealthPotion.h"

#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/RoguePlayerCharacter.h"


ARoguePickupHealthPotion::ARoguePickupHealthPotion() : ARoguePickup()
{
}

void ARoguePickupHealthPotion::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ARoguePickupHealthPotion::OnSphereOverlappedActor);
}


void ARoguePickupHealthPotion::OnSphereOverlappedActor(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                       UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                                                       bool bFromSweep,
                                                       const FHitResult& SweepResult)
{
	if (ARoguePlayerCharacter* Player = Cast<ARoguePlayerCharacter>(OtherActor))
	{
		if (Player->GetHealthPercent() < 1.f)
		{
			Player->ApplyHealthChange(20.f);
			UGameplayStatics::PlaySoundAtLocation(this, PickupSound, GetActorLocation(), FRotator::ZeroRotator);
			Destroy();
		}

		UE_LOG(LogTemp, Warning, TEXT("Pawn overlapped: %s"), *Player->GetName());
	}
}

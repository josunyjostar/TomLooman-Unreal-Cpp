// Fill out your copyright notice in the Description page of Project Settings.


#include "RoguePickupHealthPotion.h"

#include "SharedGameplayTags.h"
#include "ActionSystem/RogueActionSystemComponent.h"
#include "Components/SphereComponent.h"
#include "Core/RogueGameplayStatics.h"
#include "Kismet/GameplayStatics.h"

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
	URogueActionSystemComponent* ActionComp = OtherActor->GetComponentByClass<URogueActionSystemComponent>();

	if (ensure(ActionComp != nullptr) && !URogueGameplayStatics::IsFullHealth(ActionComp))
	{
		ActionComp->ApplyAttributeChange(SharedGameplayTags::Attribute_Health, HealingAmount, Base);
		UGameplayStatics::PlaySoundAtLocation(this, PickupSound, GetActorLocation(), FRotator::ZeroRotator);
		Destroy();
	}
}

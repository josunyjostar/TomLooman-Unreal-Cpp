// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RoguePickup.h"
#include "RoguePickupHealthPotion.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ARoguePickupHealthPotion : public ARoguePickup
{
	GENERATED_BODY()

public:
	ARoguePickupHealthPotion();
protected:
	UPROPERTY(EditDefaultsOnly, Category="Pickup")
	float HealingAmount = 50.f;
protected:
	virtual void PostInitializeComponents() override;

public:
	virtual void OnSphereOverlappedActor(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                             UPrimitiveComponent* OtherComp,
	                             int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};

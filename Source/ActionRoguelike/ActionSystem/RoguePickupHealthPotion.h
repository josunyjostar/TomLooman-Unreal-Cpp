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
	virtual void PostInitializeComponents() override;

public:
	UFUNCTION()
	void OnSphereOverlappedActor(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                             UPrimitiveComponent* OtherComp,
	                             int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};

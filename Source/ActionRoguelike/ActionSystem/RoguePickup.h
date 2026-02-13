// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RoguePickup.generated.h"

class USphereComponent;

UCLASS(Abstract)
class ACTIONROGUELIKE_API ARoguePickup : public AActor
{
	GENERATED_BODY()
public:
	ARoguePickup();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	UPROPERTY(EditDefaultsOnly, Category="Components")
	TObjectPtr<USphereComponent> SphereComponent;

	UPROPERTY(EditDefaultsOnly, Category="Sound")
	TObjectPtr<USoundBase> PickupSound;

	UPROPERTY(EditDefaultsOnly, Category="Pickup")
	float SphereRadius = 64.f;
protected:
	virtual void PostInitializeComponents() override;
public:
	UFUNCTION()
	virtual void OnSphereOverlappedActor(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                                     UPrimitiveComponent* OtherComp,
	                                     int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};

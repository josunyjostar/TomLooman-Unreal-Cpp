// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RogueInteractionComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ACTIONROGUELIKE_API URogueInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category="Interaction")
	float InteractionRadius = 800;

	UPROPERTY(EditDefaultsOnly, Category="Interaction")
	float DistWeightScale = 1.f;

	UPROPERTY(EditDefaultsOnly, Category="Interaction")
	float DirectionWeightScale = 2.f;

	UPROPERTY()
	TObjectPtr<AActor> SelectedActor;

public:
	URogueInteractionComponent();

	void Interact();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};

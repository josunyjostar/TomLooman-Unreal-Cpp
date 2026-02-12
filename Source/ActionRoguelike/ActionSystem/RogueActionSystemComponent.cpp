// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueActionSystemComponent.h"


URogueActionSystemComponent::URogueActionSystemComponent()
{

}

void URogueActionSystemComponent::ApplyHealthChange(float InValueChange)
{
	float OldHealth = InValueChange;
	Attributes.Health += InValueChange;
	
	OnHealthChanged.Broadcast(Attributes.Health, OldHealth);
}

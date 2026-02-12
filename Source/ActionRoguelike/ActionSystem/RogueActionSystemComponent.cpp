// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueActionSystemComponent.h"


URogueActionSystemComponent::URogueActionSystemComponent()
{
}

void URogueActionSystemComponent::ApplyHealthChange(float InValueChange)
{
	const float OldHealth = Attributes.Health;
	const float MaxHealth = GetDefault<URogueActionSystemComponent>()->Attributes.Health;
	Attributes.Health = FMath::Clamp(Attributes.Health + InValueChange, 0.f, MaxHealth);

	if (!FMath::IsNearlyEqual( OldHealth,Attributes.Health))
	{
		OnHealthChanged.Broadcast(Attributes.Health , OldHealth);
	}
}

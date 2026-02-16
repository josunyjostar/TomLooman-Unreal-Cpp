#include "RogueActionSystemComponent.h"

#include "RogueAction.h"

URogueActionSystemComponent::URogueActionSystemComponent()
{
	bWantsInitializeComponent = true;
}

void URogueActionSystemComponent::InitializeComponent()
{
	Super::InitializeComponent();

	for (TSubclassOf<URogueAction> ActionClass : DefaultActions)
	{
		if (ensure(ActionClass))
		{
			GrantAction(ActionClass);
		}
	}
}

void URogueActionSystemComponent::GrantAction(TSubclassOf<URogueAction> NewActionClass)
{
	URogueAction* NewAction = NewObject<URogueAction>(this, NewActionClass);
	Actions.Add(NewAction);
}

void URogueActionSystemComponent::StartAction(FName InActionName)
{
	for (URogueAction* Action : Actions)
	{
		if (Action->GetActionName() == InActionName)
		{
			Action->StartAction();
			return;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("No Action found with name %s"), *InActionName.ToString());
}

void URogueActionSystemComponent::StopAction(FName InActionName)
{
	for (URogueAction* Action : Actions)
	{
		if (Action->GetActionName() == InActionName)
		{
			Action->StopAction();
			return;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("No Action found with name %s"), *InActionName.ToString());
}


void URogueActionSystemComponent::ApplyHealthChange(float InValueChange)
{
	const float OldHealth = Attributes.Health;
	Attributes.Health = FMath::Clamp(Attributes.Health + InValueChange, 0.f, Attributes.HealthMax);

	if (!FMath::IsNearlyEqual(OldHealth, Attributes.Health))
	{
		OnHealthChanged.Broadcast(Attributes.Health, OldHealth);
	}
}

float URogueActionSystemComponent::GetHealth() const
{
	return Attributes.Health;
}

float URogueActionSystemComponent::GetHealthMax() const
{
	return Attributes.HealthMax;
}

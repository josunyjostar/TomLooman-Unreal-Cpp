#include "RogueActionSystemComponent.h"

#include "RogueAction.h"
#include "RogueAttributeSet.h"

URogueActionSystemComponent::URogueActionSystemComponent()
{
	bWantsInitializeComponent = true;
	AttributeSetClass = URogueAttributeSet::StaticClass();
}

void URogueActionSystemComponent::InitializeComponent()
{
	Super::InitializeComponent();
	
	Attributes = NewObject<URogueAttributeSet>(this, AttributeSetClass);
	
	for (TFieldIterator<FStructProperty> PropIt(Attributes->GetClass()); PropIt; ++PropIt)
	{
		FRogueAttribute* FoundAttribute = PropIt->ContainerPtrToValuePtr<FRogueAttribute>(Attributes);
		
		FName AttributeTagName = FName("Attribute." + PropIt->GetName());
		FGameplayTag AttributeTag = FGameplayTag::RequestGameplayTag(AttributeTagName);

		CachedAttributes.Add(AttributeTag, FoundAttribute);
	}

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


void URogueActionSystemComponent::StartAction(FGameplayTag InActionName)
{
	for (URogueAction* Action : Actions)
	{
		if (Action->GetActionName() == InActionName)
		{
			if (Action->CanStart())
			{
				Action->StartAction();
			}
			return;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("No Action found with name %s"), *InActionName.ToString());
}

void URogueActionSystemComponent::StopAction(FGameplayTag InActionName)
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
	// const float OldHealth = Attributes.Health;
	// Attributes.Health = FMath::Clamp(Attributes.Health + InValueChange, 0.f, Attributes.HealthMax);
	//
	// if (!FMath::IsNearlyEqual(OldHealth, Attributes.Health))
	// {
	// 	OnHealthChanged.Broadcast(Attributes.Health, OldHealth);
	// }
}

bool URogueActionSystemComponent::IsFullHealth() const
{
	return true;
}

float URogueActionSystemComponent::GetHealthPercent() const
{
	return 0.f;
}

float URogueActionSystemComponent::GetHealth() const
{
	return 0.f;
}

float URogueActionSystemComponent::GetHealthMax() const
{
	return 0.f;
}

FRogueAttribute* URogueActionSystemComponent::GetAttribute(FGameplayTag InAttributeTag)
{
	FRogueAttribute** FoundAttribute = CachedAttributes.Find(InAttributeTag);
	return *FoundAttribute;
}

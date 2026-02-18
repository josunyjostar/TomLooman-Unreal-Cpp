#include "RogueAICharacter.h"

#include "AIController.h"
#include "RogueGameTypes.h"
#include "SharedGameplayTags.h"
#include "ActionSystem/RogueActionSystemComponent.h"
#include "BehaviorTree/BlackboardComponent.h"


ARogueAICharacter::ARogueAICharacter()
{
	ActionSystemComponent = CreateDefaultSubobject<URogueActionSystemComponent>(TEXT("ActionSystemComp"));
}

float ARogueAICharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
                                    class AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	ActionSystemComponent->ApplyAttributeChange(SharedGameplayTags::Attribute_Health, -ActualDamage, Base);


	return ActualDamage;
}

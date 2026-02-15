#include "RogueAICharacter.h"

#include "AIController.h"
#include "RogueGameTypes.h"
#include "ActionSystem/RogueActionSystemComponent.h"
#include "BehaviorTree/BlackboardComponent.h"


ARogueAICharacter::ARogueAICharacter()
{
	ActionSystemComponent = CreateDefaultSubobject<URogueActionSystemComponent>(TEXT("ActionSystemComp"));
}

void ARogueAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	ActionSystemComponent->OnHealthChanged.AddDynamic(this, &ARogueAICharacter::OnHealthCanged);
	
}

float ARogueAICharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
                                    class AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	ActionSystemComponent->ApplyHealthChange(-DamageAmount);

	AAIController* AIController = Cast<AAIController>(GetController());
	AIController->GetBlackboardComponent()->
	              SetValueAsFloat(NAME_HealPercent, ActionSystemComponent->GetHealthPercent());

	return ActualDamage;
}

void ARogueAICharacter::OnHealthCanged(float NewHealth, float OldHealth)
{
	UE_LOG(LogTemp, Display, TEXT("ActualDamage: %f"), ActionSystemComponent->GetHealthPercent());
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueBTDecorator_IsLowHealth.h"

#include "AIController.h"
#include "ActionSystem/RogueActionSystemComponent.h"

class URogueActionSystemComponent;

bool URogueBTDecorator_IsLowHealth::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
                                                               uint8* NodeMemory) const
{
	APawn* Pawn = OwnerComp.GetAIOwner()->GetPawn();
	check(Pawn);
	
	URogueActionSystemComponent* ActionComp = Pawn->GetComponentByClass<URogueActionSystemComponent>();
	if (ensure(ActionComp))
	{
		check(false);
		return false;//(ActionComp->GetHealth() / ActionComp->GetHealthMax()) < LowHealthFraction;
	}
	
	return false;
}

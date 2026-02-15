// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueBTTask_Heal.h"

#include "AIController.h"
#include "ActionSystem/RogueActionSystemComponent.h"
#include "GameFramework/Character.h"

class URogueActionSystemComponent;

URogueBTTask_Heal::URogueBTTask_Heal()
{
}

EBTNodeResult::Type URogueBTTask_Heal::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	
	ACharacter* Pawn = Cast<ACharacter>(OwnerComp.GetAIOwner()->GetPawn());
	check(Pawn);
	
	URogueActionSystemComponent* ActionComp = Pawn->GetComponentByClass<URogueActionSystemComponent>();
	ActionComp->ApplyHealthChange(100.f);
	
	return EBTNodeResult::Succeeded;
}

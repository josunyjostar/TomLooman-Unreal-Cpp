// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueAIController.h"

#include "RogueGameTypes.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

ARogueAIController::ARogueAIController()
{
}


void ARogueAIController::BeginPlay()
{
	Super::BeginPlay();

	RunBehaviorTree(BehaviorTree);
	
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	check(PlayerPawn);

	GetBlackboardComponent()->SetValueAsObject(NAME_TargetActor, PlayerPawn);
	GetBlackboardComponent()->SetValueAsFloat(NAME_HealPercent, 1.0f);
}

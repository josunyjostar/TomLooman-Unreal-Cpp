#include "RogueBTService_CheckRangeTo.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

TAutoConsoleVariable<bool> CVarLineOfSightToDebugDrawing(TEXT("game.ai.DebugDraw"), false,
                                                         TEXT(
	                                                         "Enable ai LineOfSightTo debug rendering. (0 = Off, 1 = enabled)"),
                                                         ECVF_Cheat);

void URogueBTService_CheckRangeTo::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();
	check(BBComp);

	AActor* TargetActor = Cast<AActor>(BBComp->GetValueAsObject(TargetActorKey.SelectedKeyName));
	if (TargetActor)
	{
		AAIController* Controller = OwnerComp.GetAIOwner();
		APawn* OwningPawn = Controller->GetPawn();
		check(OwningPawn);

		float DistanceTo = FVector::Dist(TargetActor->GetActorLocation(), OwningPawn->GetActorLocation());
		bool bWithinRange = DistanceTo < MaxAttackRange;
		bool bHasLOS = Controller->LineOfSightTo(TargetActor);

		BBComp->SetValueAsBool(WithinRangeKey.SelectedKeyName, (bWithinRange && bHasLOS));

		bool bEnabledDebugDraw = CVarLineOfSightToDebugDrawing.GetValueOnGameThread();
		if (bEnabledDebugDraw)
		{
			FVector ViewLocation;
			FRotator ViewRotation;
			Controller->GetActorEyesViewPoint(ViewLocation, ViewRotation);

			DrawDebugSphere(GetWorld(), ViewLocation, 20.f, 12, FColor::Green, false, DeltaSeconds * 2.f);
			DrawDebugLine(GetWorld(), ViewLocation, TargetActor->GetActorLocation(), FColor::Red, false,
			              DeltaSeconds * 2.f);
		}
	}
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueInteractionComponent.h"

#include "RogueGameTypes.h"
#include "Core/RogueInteractionInterface.h"
#include "Engine/OverlapResult.h"

TAutoConsoleVariable<bool> CVarInteractionDebugDrawing(TEXT("game.interaction.DebugDraw"), false,
                                                       TEXT(
	                                                       "Enable interaction component debug rendering. (0 = Off, 1 = enabled)"),
                                                       ECVF_Cheat);

URogueInteractionComponent::URogueInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void URogueInteractionComponent::Interact()
{
	if (SelectedActor && SelectedActor->Implements<URogueInteractionInterface>())
	{
		IRogueInteractionInterface::Execute_Interact(SelectedActor);
	}
}

void URogueInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                               FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	APlayerController* PC = CastChecked<APlayerController>(GetOwner());

	FVector Center = PC->GetPawn()->GetActorLocation();
	FVector CameraLocation = PC->PlayerCameraManager->GetCameraLocation();
	ECollisionChannel CollisionChannel = COLLISION_INTERACTION;

	FCollisionShape Shape;
	Shape.SetSphere(InteractionRadius);
	float InteractionRadiusSquared = InteractionRadius * InteractionRadius;

	TArray<FOverlapResult> Overlaps;
	GetWorld()->OverlapMultiByChannel(Overlaps, Center, FQuat::Identity, CollisionChannel, Shape);

	AActor* BestActor = nullptr;
	float HighestWeight = 0.0;

	bool bEnabledDebugDraw = CVarInteractionDebugDrawing.GetValueOnGameThread();

	for (FOverlapResult& Overlap : Overlaps)
	{
		FVector Origin;
		FVector BoxExtends;
		Overlap.GetActor()->GetActorBounds(true,Origin,BoxExtends);
		
		FVector OverlapLocation = Overlap.GetActor()->GetActorLocation();
		FVector OverlapDirection = (Origin - CameraLocation).GetSafeNormal();
		float DistanceToSquared = (Origin - CameraLocation).SizeSquared();
		float NormalizedDistance = 1.f - (DistanceToSquared / InteractionRadiusSquared);

		float DotResult = FVector::DotProduct(OverlapDirection, PC->GetControlRotation().Vector());
		float NormalizedDotResult = DotResult * 0.5f + 0.5f;
		float Wieght = (NormalizedDotResult * DirectionWeightScale) + (NormalizedDistance * DistWeightScale);
		if (Wieght > HighestWeight)
		{
			BestActor = Overlap.GetActor();
			HighestWeight = Wieght;
		}

		if (bEnabledDebugDraw)
		{
			DrawDebugBox(GetWorld(), Origin, FVector(50.0f), FColor::Red);
			FString DebugString = FString::Printf(
				TEXT("Wight: %f Dot: %f Dist: %f"), Wieght, NormalizedDotResult, NormalizedDistance);
			DrawDebugString(GetWorld(), Origin, DebugString, nullptr, FColor::White, 0.0f, true);
		}
	}

	SelectedActor = BestActor;

	if (bEnabledDebugDraw)
	{
		if (BestActor)
			DrawDebugBox(GetWorld(), BestActor->GetActorLocation(), FVector(60.0f), FColor::Green);

		DrawDebugSphere(GetWorld(), Center, InteractionRadius, 32, FColor::White);
	}
}

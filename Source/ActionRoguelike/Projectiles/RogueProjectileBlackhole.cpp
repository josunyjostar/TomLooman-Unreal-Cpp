// Fill out your copyright notice in the Description page of Project Settings.

#include "RogueProjectileBlackhole.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"

ARogueProjectileBlackhole::ARogueProjectileBlackhole()
{
	SphereComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
	SphereComponent->SetGenerateOverlapEvents(true);

	ProjectileMovementComponent->InitialSpeed = 300.f;

	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComp"));
	RadialForceComponent->SetupAttachment(SphereComponent);
	RadialForceComponent->ForceStrength = -200000.0f;
	RadialForceComponent->Radius = 750.f;
	RadialForceComponent->bAutoActivate = true;
	RadialForceComponent->bIgnoreOwningActor = true;
}

void ARogueProjectileBlackhole::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ARogueProjectileBlackhole::OnOverlap);
}

void ARogueProjectileBlackhole::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherComp && OtherComp->IsSimulatingPhysics())
	{
		OtherActor->Destroy();
	}
}

void ARogueProjectileBlackhole::DestroySelf()
{
	Destroy();
}

void ARogueProjectileBlackhole::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ARogueProjectileBlackhole::DestroySelf, 5.f);
}

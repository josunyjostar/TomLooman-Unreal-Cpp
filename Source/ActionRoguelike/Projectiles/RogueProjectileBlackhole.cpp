// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueProjectileBlackhole.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"



ARogueProjectileBlackhole::ARogueProjectileBlackhole()
{
	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComponent"));
	RadialForceComponent->SetupAttachment(RootComponent);
	RadialForceComponent->ForceStrength = -800000.0f; 
	RadialForceComponent->Radius = 1200.0f;
	
	RadialForceComponent->RemoveObjectTypeToAffect(UEngineTypes::ConvertToObjectType(ECC_Pawn));
	
	SphereComponent->SetSphereRadius(20.0f);
	SphereComponent->SetCollisionProfileName("BlackholeCore");
	
	ProjectileMovementComponent->InitialSpeed = 500.0f;
	
	InitialLifeSpan = 5.0f;
}

void ARogueProjectileBlackhole::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	// Note: Make sure GenerateOverlapEvents is enabled on the cubes in the world
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ARogueProjectileBlackhole::OnSphereOverlappedActor);
	GetInstigator()->MoveIgnoreActorAdd(this);
}

void ARogueProjectileBlackhole::OnSphereOverlappedActor(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherComp->IsSimulatingPhysics())
	{
		OtherActor->Destroy();
	}
}

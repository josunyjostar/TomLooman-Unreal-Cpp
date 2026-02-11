// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueProjectileTeleport.h"

#include "NiagaraFunctionLibrary.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
ARogueProjectileTeleport::ARogueProjectileTeleport()
{
	ProjectileMovementComponent->InitialSpeed = 1500.f;
}

void ARogueProjectileTeleport::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle,this,&ARogueProjectileTeleport::Teleport,0.4f);
}

void ARogueProjectileTeleport::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SphereComponent->OnComponentHit.AddDynamic(this, &ARogueProjectileTeleport::OnActorHit);
}

void ARogueProjectileTeleport::Explode()
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ExplosionEffect, GetActorLocation());
	Destroy();
}

void ARogueProjectileTeleport::Teleport()
{
	ProjectileMovementComponent->StopMovementImmediately();
	GetInstigator()->SetActorLocation(GetActorLocation());
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle,this,&ARogueProjectileTeleport::Explode,0.2f);
}

void ARogueProjectileTeleport::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                                          UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Teleport();
}

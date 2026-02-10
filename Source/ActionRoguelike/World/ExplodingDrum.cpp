// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplodingDrum.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
AExplodingDrum::AExplodingDrum()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh Comp"));
	RootComponent = StaticMeshComponent; // 이게 Root!

	StaticMeshComponent->SetSimulatePhysics(true);
	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	
	RadialForce = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForce"));
	RadialForce->SetupAttachment(RootComponent);
	RadialForce->Radius = 150.0f;
	RadialForce->ImpulseStrength = 300.0f;
	RadialForce->bImpulseVelChange = false ;
	RadialForce->bIgnoreOwningActor = false; 
}

// Called when the game starts or when spawned
void AExplodingDrum::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AExplodingDrum::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float AExplodingDrum::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
                                 AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (ActiveBurningVFX)
	{
		Explode();
		return 0.f;
	}

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AExplodingDrum::Burning, 0.7f, false);

	return 0.f;
}

void AExplodingDrum::Burning()
{
	ActiveBurningVFX = UNiagaraFunctionLibrary::SpawnSystemAttached(
		BurningEffect,
		StaticMeshComponent, // 드럼통 메시에 붙임
		NAME_None,
		FVector(0, 0, 50), // 드럼통 위쪽
		FRotator::ZeroRotator,
		EAttachLocation::KeepRelativeOffset, // 상대 위치 유지
		false // 자동 삭제 안 함
	);

	BurningAudioComponent = UGameplayStatics::SpawnSound2D(
		this,
		BurningSound,
		1.0f, // Volume
		1.0f, // Pitch
		0.0f, // Start Time
		nullptr, // Concurrency Settings
		false, // Persist Across Level Transition
		true // ← Auto Destroy (나중에 Stop하면 자동 삭제)
	);
}

void AExplodingDrum::Explode()
{
	if (BurningAudioComponent)
		BurningAudioComponent->Stop();

	if (ActiveBurningVFX)
		ActiveBurningVFX->DeactivateImmediate();
	
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ExplosionEffect, GetActorLocation(),
	                                               FRotator::ZeroRotator);
	
	UGameplayStatics::PlaySound2D(this, ExplosionSound);
	RadialForce->FireImpulse();
	DrawDebugSphere(GetWorld(), RadialForce->GetComponentLocation(), 
				  RadialForce->Radius, 16, FColor::Red, false, 2.0f);
	FTimerHandle DestroyTimer;
	GetWorldTimerManager().SetTimer(DestroyTimer, [this]()
	{
		Destroy();
	}, 0.1f, false); // 0.1초 후 삭제
}

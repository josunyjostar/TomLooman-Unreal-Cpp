#include "RoguePickup.h"
#include "Components/SphereComponent.h"

ARoguePickup::ARoguePickup()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComponent->SetSphereRadius(SphereRadius);
	RootComponent = SphereComponent;
	SphereComponent->SetCollisionProfileName(TEXT("Pickups"));

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
	StaticMeshComponent->SetupAttachment(RootComponent);
	StaticMeshComponent->SetCollisionProfileName("NoCollision");
}

void ARoguePickup::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ARoguePickup::OnSphereOverlappedActor(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}


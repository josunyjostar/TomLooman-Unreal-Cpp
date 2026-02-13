#include "RoguePickup.h"

#include "RogueActionSystemComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/RoguePlayerCharacter.h"

ARoguePickup::ARoguePickup()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComponent->SetSphereRadius(SphereRadius);
	RootComponent = SphereComponent;
	SphereComponent->SetCollisionProfileName(TEXT("Pickups"));

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
	StaticMeshComponent->SetupAttachment(RootComponent);
}


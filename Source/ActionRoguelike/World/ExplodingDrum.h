// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExplodingDrum.generated.h"

class UNiagaraComponent;
class UNiagaraSystem;
class UCapsuleComponent;
class URadialForceComponent;

UCLASS()
class ACTIONROGUELIKE_API AExplodingDrum : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AExplodingDrum();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	                 AActor* DamageCauser) override;

	UPROPERTY(EditDefaultsOnly, Category="Effects")
	TObjectPtr<UNiagaraSystem> BurningEffect;
	
	UPROPERTY(EditDefaultsOnly, Category="Effects")
	TObjectPtr<UNiagaraSystem> ExplosionEffect;
	
	UPROPERTY(EditDefaultsOnly, Category="Components")
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
	
	UPROPERTY()
	TObjectPtr<UNiagaraComponent> ActiveBurningVFX;  
	
	UPROPERTY(EditDefaultsOnly, Category="Sound")
	TObjectPtr<USoundBase> BurningSound;
	
	UPROPERTY()
	TObjectPtr<UAudioComponent> BurningAudioComponent;  
	
	UPROPERTY(EditDefaultsOnly, Category="Sound")
	TObjectPtr<USoundBase> ExplosionSound;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<URadialForceComponent> RadialForce;
	
private:
	void Burning();
	void Explode();
};

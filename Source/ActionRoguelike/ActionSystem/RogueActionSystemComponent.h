// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RogueActionSystemComponent.generated.h"


struct FGameplayTag;
class URogueAction;

USTRUCT(BlueprintType)
struct FRogueAttributeSet
{
	GENERATED_BODY()
	FRogueAttributeSet()
		: Health(100.0f), HealthMax(100.f)
	{
	}

	UPROPERTY(BlueprintReadOnly)
	float Health;

	UPROPERTY(BlueprintReadOnly)
	float HealthMax;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, NewHealth, float, OldHealth);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ACTIONROGUELIKE_API URogueActionSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	virtual void InitializeComponent() override;
	void GrantAction(TSubclassOf<URogueAction> NewActionClass);

	void StartAction(FGameplayTag InActionName);
	void StopAction(FGameplayTag InActionName);

	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;
	void ApplyHealthChange(float InValueChange);
	float IsFullHealth() const { return (Attributes.Health < Attributes.HealthMax); }
	float GetHealthPercent() const { return Attributes.Health / Attributes.HealthMax; }
	float GetHealth() const;
	float GetHealthMax() const;

protected:
	UPROPERTY(BlueprintReadOnly, Category="Attributes")
	FRogueAttributeSet Attributes;

	UPROPERTY()
	TArray<TObjectPtr<URogueAction>> Actions;
	
	UPROPERTY(EditAnywhere, Category="Actions")
	TArray<TSubclassOf<URogueAction>> DefaultActions;

public:
	URogueActionSystemComponent();
};

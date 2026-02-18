// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "RogueActionSystemComponent.generated.h"

struct FRogueAttribute;
class URogueAttributeSet;
class URogueAction;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, NewHealth, float, OldHealth);

UENUM()
enum EAttributeModifyType
{
	Base,
	Modifier,
	OverrideBase,
	Invalid
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ACTIONROGUELIKE_API URogueActionSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	void StartAction(FGameplayTag InActionName);
	void StopAction(FGameplayTag InActionName);
	void ApplyAttributeChange(FGameplayTag AttributeTag, float Delta, EAttributeModifyType ModifyType);

	FRogueAttribute* GetAttribute(FGameplayTag InAttributeTag);

	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;

	virtual void InitializeComponent() override;

	void GrantAction(TSubclassOf<URogueAction> NewActionClass);

	FGameplayTagContainer ActiveGameplayTags;

protected:
	UPROPERTY()
	TObjectPtr<URogueAttributeSet> Attributes;

	TMap<FGameplayTag, FRogueAttribute*> CachedAttributes;

	UPROPERTY(EditAnywhere, Category=Attributes, NoClear)
	TSubclassOf<URogueAttributeSet> AttributeSetClass;

	UPROPERTY()
	TArray<TObjectPtr<URogueAction>> Actions;

	UPROPERTY(EditAnywhere, Category="Actions")
	TArray<TSubclassOf<URogueAction>> DefaultActions;

public:
	URogueActionSystemComponent();
};

#include "RoguePlayerCharacter.h"

#include "EnhancedInputComponent.h"
#include "GameplayTagContainer.h"
#include "SharedGameplayTags.h"
#include "ActionSystem/RogueActionSystemComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"


ARoguePlayerCharacter::ARoguePlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	ActionSystemComponent = CreateDefaultSubobject<URogueActionSystemComponent>(TEXT("ActionSystemComp"));
}

void ARoguePlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	ActionSystemComponent->OnHealthChanged.AddDynamic(this, &ARoguePlayerCharacter::OnHealthChanged);
}

void ARoguePlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInput->BindAction(Input_Move, ETriggerEvent::Triggered, this, &ARoguePlayerCharacter::Move);
	EnhancedInput->BindAction(Input_Look, ETriggerEvent::Triggered, this, &ARoguePlayerCharacter::Look);
	EnhancedInput->BindAction(Input_Jump, ETriggerEvent::Triggered, this, &ARoguePlayerCharacter::Jump);

	EnhancedInput->BindAction(Input_Sprint, ETriggerEvent::Started, this,
	                          &ThisClass::StartAction, SharedGameplayTags::Action_Sprint.GetTag());

	EnhancedInput->BindAction(Input_Sprint, ETriggerEvent::Completed, this,
	                          &ThisClass::StopAction, SharedGameplayTags::Action_Sprint.GetTag());
	
	EnhancedInput->BindAction(Input_PrimaryAttack, ETriggerEvent::Completed, this,
							  &ThisClass::StartAction, SharedGameplayTags::Action_PrimaryAttack.GetTag());
	EnhancedInput->BindAction(Input_SecondaryAttack, ETriggerEvent::Completed, this,
						  &ThisClass::StartAction, SharedGameplayTags::Action_SecondaryAttack.GetTag());
	EnhancedInput->BindAction(Input_SpecialAttack, ETriggerEvent::Completed, this,
						  &ThisClass::StartAction, SharedGameplayTags::Action_SpecialAttack.GetTag());

}

void ARoguePlayerCharacter::Move(const FInputActionValue& InValue)
{
	FVector2D InputValue = InValue.Get<FVector2D>();

	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;

	// Forward/Back
	AddMovementInput(ControlRot.Vector(), InputValue.X);

	// Sideways
	FVector RightDirection = ControlRot.RotateVector(FVector::RightVector);
	AddMovementInput(RightDirection, InputValue.Y);
}

void ARoguePlayerCharacter::Look(const FInputActionInstance& InValue)
{
	FVector2D InputValue = InValue.GetValue().Get<FVector2D>();

	AddControllerPitchInput(InputValue.Y);
	AddControllerYawInput(InputValue.X);
}


float ARoguePlayerCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
                                        class AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	ActionSystemComponent->ApplyAttributeChange(SharedGameplayTags::Attribute_Health, -ActualDamage, Base);

	return ActualDamage;
}

void ARoguePlayerCharacter::OnHealthChanged(float NewHealth, float OldHealth)
{
	if (FMath::IsNearlyZero(NewHealth))
	{
		DisableInput(nullptr);
		GetMovementComponent()->StopMovementImmediately();
		PlayAnimMontage(DeathMontage);
	}
}

void ARoguePlayerCharacter::StartAction(FGameplayTag InActionName)
{
	ActionSystemComponent->StartAction(InActionName);
}

void ARoguePlayerCharacter::StopAction(FGameplayTag InActionName)
{
	ActionSystemComponent->StopAction(InActionName);
}

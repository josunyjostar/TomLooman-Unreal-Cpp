// Fill out your copyright notice in the Description page of Project Settings.

#include "RoguePlayerCharacter.h"

#include "Projectiles/RogueProjectileBase.h"
#include "EnhancedInputComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

ARoguePlayerCharacter::ARoguePlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	MuzzleSocketName = "Muzzle_01";
}

void ARoguePlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ARoguePlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInput->BindAction(Input_Move, ETriggerEvent::Triggered, this, &ARoguePlayerCharacter::Move);
	EnhancedInput->BindAction(Input_Look, ETriggerEvent::Triggered, this, &ARoguePlayerCharacter::Look);
	EnhancedInput->BindAction(Input_Jump, ETriggerEvent::Triggered, this, &ACharacter::Jump);

	EnhancedInput->BindAction(Input_PrimaryAttack, ETriggerEvent::Triggered, this,
	                          &ARoguePlayerCharacter::PrimaryAttack);
	EnhancedInput->BindAction(Input_BlackHoleAttack, ETriggerEvent::Started, this,
	                          &ARoguePlayerCharacter::BlackHoleAttack);
	EnhancedInput->BindAction(Input_Teleport, ETriggerEvent::Started, this, &ARoguePlayerCharacter::Teleport);
}

void ARoguePlayerCharacter::Move(const FInputActionValue& InValue)
{
	FVector2D InputValue = InValue.Get<FVector2D>();

	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;

	AddMovementInput(ControlRot.Vector(), InputValue.X);

	FVector RightDirection = ControlRot.RotateVector(FVector::RightVector);
	AddMovementInput(RightDirection, InputValue.Y);
}

void ARoguePlayerCharacter::Look(const FInputActionInstance& InValue)
{
	FVector2D InputValue = InValue.GetValue().Get<FVector2D>();

	AddControllerPitchInput(InputValue.Y);
	AddControllerYawInput(InputValue.X);
}

void ARoguePlayerCharacter::SpawnProjectile(TSubclassOf<ARogueProjectileBase> InClass)
{
	FVector SpawnLocation = GetMesh()->GetSocketLocation(MuzzleSocketName);
	FRotator SpawnRotation = GetControlRotation();
	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GetWorld()->SpawnActor<AActor>(InClass, SpawnLocation, SpawnRotation, SpawnParams);
}

void ARoguePlayerCharacter::StartAttack(TSubclassOf<ARogueProjectileBase> InClass)
{
	PlayAnimMontage(AttackMontage);

	UNiagaraFunctionLibrary::SpawnSystemAttached(CastingEffect, GetMesh(), MuzzleSocketName,
	                                             FVector::ZeroVector, FRotator::ZeroRotator,
	                                             EAttachLocation::Type::SnapToTarget, true);

	FTimerHandle Handle;
	FTimerDelegate Delegate;
	Delegate.BindUObject(this, &ARoguePlayerCharacter::SpawnProjectile, InClass);
	GetWorldTimerManager().SetTimer(Handle, Delegate, AttackDelay, false);
}

void ARoguePlayerCharacter::PrimaryAttack()
{
	StartAttack(ProjectileClass);
	UGameplayStatics::PlaySound2D(this, CastingSound);
}

void ARoguePlayerCharacter::BlackHoleAttack()
{
	StartAttack(BlackHoleClass);
}

void ARoguePlayerCharacter::Teleport()
{
	StartAttack(TeleportClass);
}

void ARoguePlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Fill out your copyright notice in the Description page of Project Settings.

#include "PSBaseCharacter.h"
#include "AbilitySystemGlobals.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
APSBaseCharacter::APSBaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AttributeSet = CreateDefaultSubobject<UPSCharacterAttributeSet>(TEXT("AttributeSet"));
}

// Called to bind functionality to input
void APSBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

UAbilitySystemComponent* APSBaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void APSBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetMoveSpeedAttribute()).AddUObject(
		this, &APSBaseCharacter::OnMoveSpeedAttributeChanged);

	for (const TSubclassOf<UPSGameplayAbility>& StartupAbility : CharacterAbilities)
	{
		AbilitySystemComponent->GiveAbility(
			FGameplayAbilitySpec(StartupAbility, 1,
			                     static_cast<int32>(StartupAbility.GetDefaultObject()->AbilityInputID), this));
	}

	// AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent, FGameplayAbilityInputBinds(
	// 	                                                              FString("ConfirmTarget"),
	// 	                                                              FString("CancelTarget"),
	// 	                                                              FString("EPSAbilityInputID"),
	// 	                                                              static_cast<int32>(EPSAbilityInputID::Confirm),
	// 	                                                              static_cast<int32>(EPSAbilityInputID::Cancel)));
}

void APSBaseCharacter::OnMoveSpeedAttributeChanged(const FOnAttributeChangeData& Data) const
{
	GetCharacterMovement()->MaxWalkSpeed = AttributeSet->GetMoveSpeed();
}

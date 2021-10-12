// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Abilities/PSCharacterAttributeSet.h"
#include "Abilities/PSGameplayAbility.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "PSBaseCharacter.generated.h"

UCLASS()
class PLANETSHARDS_API APSBaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	void OnMoveSpeedAttributeChanged(const FOnAttributeChangeData& Data) const;

	// Implement IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	// Sets default values for this character's properties
	APSBaseCharacter();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY()
	UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY()
	UPSCharacterAttributeSet* AttributeSet;

	// Default abilities for this Character. These will be removed on Character death and regiven if Character respawns.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "PlanetShards|Abilities")
	TArray<TSubclassOf<class UPSGameplayAbility>> CharacterAbilities;
};

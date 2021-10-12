// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "PSCharacterAttributeSet.generated.h"

// Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class PLANETSHARDS_API UPSCharacterAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UPSCharacterAttributeSet();

	/** Current Health, when 0 we expect owner to die. Capped by MaxHealth */
	UPROPERTY(BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UPSCharacterAttributeSet, Health)

	/** MaxHealth is its own attribute, since GameplayEffects may modify it */
	UPROPERTY(BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UPSCharacterAttributeSet, MaxHealth)

	/** MoveSpeed affects how fast characters can move */
	UPROPERTY(BlueprintReadOnly, Category = "MoveSpeed")
	FGameplayAttributeData MoveSpeed;
	ATTRIBUTE_ACCESSORS(UPSCharacterAttributeSet, MoveSpeed)
};

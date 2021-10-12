// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "PSWeapon.generated.h"

UCLASS()
class PLANETSHARDS_API APSWeapon : public AActor, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APSWeapon();

	// How much ammo in the clip the gun starts with
	UPROPERTY(EditAnywhere, Category = "PlanetShards|PSWeapon|Ammo")
	int32 ClipAmmo;

	UPROPERTY(EditAnywhere, Category = "PlanetShards|GSWeapon|Ammo")
	int32 MaxClipAmmo;

	UPROPERTY(EditAnywhere, Category = "PlanetShards|GSWeapon")
	float FiringRange;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "PlanetShards|GSWeapon")
	FGameplayTag AmmoType;

	// Implement IAbilitySystemInterface
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	UAbilitySystemComponent* AbilitySystemComponent;
};

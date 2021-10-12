// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/PSWeapon.h"

// Sets default values
APSWeapon::APSWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

UAbilitySystemComponent* APSWeapon::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

// Called when the game starts or when spawned
void APSWeapon::BeginPlay()
{
	Super::BeginPlay();
}



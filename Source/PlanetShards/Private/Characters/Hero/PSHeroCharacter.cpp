// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Hero/PSHeroCharacter.h"

#include "PSInfoMessage.h"
#include "PSInventoryComponent.h"

APSHeroCharacter::APSHeroCharacter()
{
	InventoryComponent = CreateDefaultSubobject<UPSInventoryComponent>(FName("InventoryComponent"));
	InventoryComponent->Size.X = 6;
	InventoryComponent->Size.Y = 6;
	InventoryComponent->FullInventoryText = FText::FromString(TEXT("Inventory is full!"));
}

void APSHeroCharacter::BeginPlay()
{
	Super::BeginPlay();
	InventoryComponent->MessageWidgetClass = MessageWidgetClass;
}

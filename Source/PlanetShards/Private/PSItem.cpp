// Fill out your copyright notice in the Description page of Project Settings.


#include "PSItem.h"
#include "PSInventoryComponent.h"
#include "Engine/UserInterfaceSettings.h"

void APSItem::OnInteract_Implementation(const AActor* Interacting)
{
	UPSInventoryComponent* Inventory = Interacting->FindComponentByClass<UPSInventoryComponent>();
	Inventory->AddToInventory(this);
}

void APSItem::BeginPlay()
{
	Super::BeginPlay();
}

// Sets default values
APSItem::APSItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

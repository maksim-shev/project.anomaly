// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PSTypes.generated.h"

USTRUCT(Blueprintable)
struct PLANETSHARDS_API FItemData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsStackable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxStackCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Thumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AActor> ItemClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FIntPoint Size;
};

USTRUCT(BlueprintType, Blueprintable)
struct PLANETSHARDS_API FSlot
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FItemData Item;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Quantity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FIntPoint Coordinates;

	FSlot()
	{
	}

	FSlot(FItemData InItem, int32 InQuantity, FIntPoint InCoordinates) :
		Item(InItem),
		Quantity(InQuantity),
		Coordinates(InCoordinates)
	{
	}
};

UENUM(BlueprintType)
enum class EPSAbilityInputID : uint8
{
	// 0 None
	None UMETA(DisplayName = "None"),
	// 1 Confirm
	Confirm UMETA(DisplayName = "Confirm"),
	// 2 Cancel
	Cancel UMETA(DisplayName = "Cancel"),
	// 3 Sprint
	Sprint UMETA(DisplayName = "Sprint"),
	// 4 Jump
	Jump UMETA(DisplayName = "Jump"),
	// 5 PrimaryFire
	PrimaryFire UMETA(DisplayName = "Primary Fire"),
	// 6 SecondaryFire
	SecondaryFire UMETA(DisplayName = "Secondary Fire"),
	// 7 Alternate Fire
	AlternateFire UMETA(DisplayName = "Alternate Fire"),
	// 8 Reload
	Reload UMETA(DisplayName = "Reload"),
	// 9 NextWeapon
	NextWeapon UMETA(DisplayName = "Next Weapon"),
	// 10 PrevWeapon
	PrevWeapon UMETA(DisplayName = "Previous Weapon"),
	// 11 Interact
	Interact UMETA(DisplayName = "Interact")
};

//USTRUCT()
//struct PLANETSHARDS_API PSHeroEquipment
//{
//	GENERATED_USTRUCT_BODY()
//
//		UPROPERTY()
//		TArray<PSWeapon*> Weapons;
//
//	// Consumable items
//
//	// Passive items like armor
//
//	// Door keys
//
//	// Etc
//};

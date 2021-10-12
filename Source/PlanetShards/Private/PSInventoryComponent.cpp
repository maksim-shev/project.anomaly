// Fill out your copyright notice in the Description page of Project Settings.


#include "PSInventoryComponent.h"
#include "PSUseInterface.h"
#include "PSItem.h"
#include "PSInfoMessage.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>

TArray<FIntPoint> UPSInventoryComponent::GetEmptySlots()
{
	TArray<FIntPoint> Result;
	for (int32 i = 0; i < Grid.Num(); i++)
	{
		for (int32 j = 0; j < Grid[i].Num(); j++)
		{
			if (Grid[i][j])
			{
				Result.Add(FIntPoint(i, j));
			}
		}
	}
	return Result;
}

// Sets default values for this component's properties
UPSInventoryComponent::UPSInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPSInventoryComponent::RemoveItemFromSlot(const int32 SlotIndex, const int32 Quantity)
{
	if (!Inventory.IsValidIndex(SlotIndex))
	{
		return;
	}
	FSlot Slot = Inventory[SlotIndex];
	Slot.Quantity -= Quantity;
	if (Slot.Quantity < 0)
	{
		RemoveSlotFromInventory(SlotIndex);
		return;
	}
	Inventory[SlotIndex] = Slot;
}

TOptional<int32> UPSInventoryComponent::AddToInventory(APSItem* Item)
{
	const FItemData ItemData = Item->ItemInfo;
	TOptional<int32> Result;
	if (ItemData.IsStackable)
	{
		Result = FindExistingSlot(Item);
		if (Result.IsSet())
		{
			const int32 ResultingQuantity = Inventory[Result.GetValue()].Quantity + Item->Quantity;
			if (ResultingQuantity > Item->ItemInfo.MaxStackCount)
			{
				Inventory[Result.GetValue()].Quantity = Item->ItemInfo.MaxStackCount;
				Item->Quantity = ResultingQuantity - Item->ItemInfo.MaxStackCount;
				AddToInventory(Item);
			}
			else
			{
				Inventory[Result.GetValue()].Quantity += Item->Quantity;
				Item->Destroy();
			}
		}
	}
	if (!Result.IsSet())
	{
		FSlot Slot;
		Slot.Quantity = Item->Quantity;
		Slot.Item = ItemData;
		bool Success;
		Slot.Coordinates = FindAvailableArea(ItemData, Success);
		if (Success)
		{
			SetAreaFilled(Slot.Coordinates, Slot.Item.Size);
			Item->Destroy();
			Result = Inventory.Add(Slot);
		}
		if (!Result.IsSet())
		{
			ShowFullInventoryMessage();
		}
	}
	return Result;
}

int32 UPSInventoryComponent::AddToInventory(const FItemData Item, const int32 Quantity, const FIntPoint Coordinates)
{
	FSlot Slot;
	Slot.Quantity = Quantity;
	Slot.Item = Item;
	Slot.Coordinates = Coordinates;
	SetAreaFilled(Slot.Coordinates, Slot.Item.Size);
	return Inventory.Add(Slot);
}

void UPSInventoryComponent::RemoveSlotFromInventory(const int32 SlotIndex)
{
	if (!Inventory.IsValidIndex(SlotIndex))
	{
		return;
	}
	const FSlot Slot = Inventory[SlotIndex];
	Inventory.RemoveAt(SlotIndex, 1, false);
	SetAreaEmpty(Slot.Coordinates, Slot.Item.Size);
}

bool UPSInventoryComponent::CheckSlotAvailability(const FIntPoint Coordinates)
{
	if (Coordinates.X < Grid.Num() && Coordinates.X >= 0)
	{
		if (Coordinates.Y < Grid[Coordinates.X].Num() && Coordinates.Y >= 0)
		{
			return Grid[Coordinates.X][Coordinates.Y];
		}
	}
	return false;
}

void UPSInventoryComponent::UseItem(const int32 SlotIndex, const int32 Quantity)
{
	if (!Inventory.IsValidIndex(SlotIndex))
	{
		return;
	}
	FSlot Slot = Inventory[SlotIndex];
	const APSItem* Item = static_cast<APSItem*>(GetWorld()->SpawnActor(Slot.Item.ItemClass));
	const APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (Item->GetClass()->ImplementsInterface(UPSInteractInterface::StaticClass()))
	{
		const bool Success = IPSUseInterface::Execute_Use(Item, PlayerPawn);
		if (Success)
		{
			Slot.Quantity -= Quantity;
			if (Slot.Quantity == 0)
			{
				RemoveSlotFromInventory(SlotIndex);
				return;
			}
			Inventory[SlotIndex] = Slot;
		}
	}
}

void UPSInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	TArray<bool> Row;
	Row.Init(true, this->Size.X);
	Grid.Init(Row, this->Size.Y);
}

TOptional<int32> UPSInventoryComponent::FindExistingSlot(const APSItem* Item)
{
	TOptional<int32> Result;
	for (uint16 i = 0; i < Inventory.Num(); i++)
	{
		FSlot Slot = Inventory[i];
		if (Slot.Item.ItemClass == Item->GetClass() && Slot.Quantity < Slot.Item.MaxStackCount)
		{
			Result = i;
		}
	}
	return Result;
}

FIntPoint UPSInventoryComponent::FindAvailableArea(const FItemData FItemData, bool& Success)
{
	Success = false;
	for (int32 GridX = 0; GridX < Size.X; GridX++)
	{
		for (int32 GridY = 0; GridY < Size.Y; GridY++)
		{
			bool IsCurrentAreaAvailable = true;
			for (int32 ItemX = GridX; ItemX < GridX + FItemData.Size.X; ItemX++)
			{
				if (ItemX == Size.X)
				{
					IsCurrentAreaAvailable = false;
					break;
				}
				for (int32 ItemY = GridY; ItemY < GridY + FItemData.Size.Y; ItemY++)
				{
					if (ItemY == Size.Y)
					{
						IsCurrentAreaAvailable = false;
						break;
					}
					IsCurrentAreaAvailable = Grid[ItemX][ItemY];
					if (!IsCurrentAreaAvailable)
					{
						break;
					}
				}
				if (!IsCurrentAreaAvailable)
				{
					break;
				}
			}
			if (IsCurrentAreaAvailable)
			{
				Success = true;
				return FIntPoint(GridX, GridY);
			}
		}
	}
	this->ShowFullInventoryMessage();
	return FIntPoint();
}

void UPSInventoryComponent::SetAreaFilled(const FIntPoint Coordinates, const FIntPoint ItemSize)
{
	for (int32 i = Coordinates.X; i < Coordinates.X + ItemSize.X; i++)
	{
		for (int32 j = Coordinates.Y; j < Coordinates.Y + ItemSize.Y; j++)
		{
			Grid[i][j] = false;
		}
	}
}

void UPSInventoryComponent::SetAreaEmpty(const FIntPoint Coordinates, const FIntPoint AreaSize)
{
	for (int32 i = Coordinates.X; i < Coordinates.X + AreaSize.X; i++)
	{
		for (int32 j = Coordinates.Y; j < Coordinates.Y + AreaSize.Y; j++)
		{
			Grid[i][j] = true;
		}
	}
}

void UPSInventoryComponent::ShowFullInventoryMessage()
{
	if (IsValid(MessageWidgetClass))
	{
		MessageWidget = Cast<UPSInfoMessage>(CreateWidget(GetWorld(), MessageWidgetClass));
		if (MessageWidget != nullptr)
		{
			MessageWidget->ShowInfoMessage(FullInventoryText);
		}
	}
}

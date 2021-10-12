// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PSItem.h"
#include "Components/ActorComponent.h"
#include "PSTypes.h"
#include "PSInventoryComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PLANETSHARDS_API UPSInventoryComponent final : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FIntPoint Size;

	UPROPERTY(EditAnywhere)
	FText FullInventoryText;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> MessageWidgetClass;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	TArray<FSlot> Inventory;

	UFUNCTION(BlueprintCallable)
	TArray<FIntPoint> GetEmptySlots();

	UFUNCTION(BlueprintCallable)
	void RemoveSlotFromInventory(int32 SlotIndex);

	UFUNCTION(BlueprintCallable)
	bool CheckSlotAvailability(FIntPoint Coordinates);

	UFUNCTION(BlueprintCallable)
	FIntPoint FindAvailableArea(FItemData FItemData, bool& Success);

	UFUNCTION(BlueprintCallable)
	int32 AddToInventory(FItemData Item, int32 Quantity, FIntPoint Coordinates);

	TOptional<int32> AddToInventory(APSItem* Item);

	UFUNCTION(BlueprintCallable)
	void RemoveItemFromSlot(int32 SlotIndex, int32 Quantity);

	UFUNCTION(BlueprintCallable)
	void UseItem(int32 SlotIndex, int32 Quantity = 1);

	virtual void BeginPlay() override;

	// Sets default values for this component's properties
	UPSInventoryComponent();

private:
	TArray<TArray<bool>> Grid;

	UPROPERTY()
	class UPSInfoMessage* MessageWidget;

	TOptional<int32> FindExistingSlot(const APSItem* Item);

	void SetAreaFilled(FIntPoint Coordinates, FIntPoint ItemSize);

	void SetAreaEmpty(FIntPoint Coordinates, FIntPoint AreaSize);

	void ShowFullInventoryMessage();
};
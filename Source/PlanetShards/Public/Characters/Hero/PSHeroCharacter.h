// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PSBaseCharacter.h"
#include "PSHeroCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PLANETSHARDS_API APSHeroCharacter final : public APSBaseCharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> MessageWidgetClass;
	
	UPROPERTY(BlueprintReadOnly, Category = "PlanetShards|Inventory")
	class UPSInventoryComponent* InventoryComponent;

	APSHeroCharacter();
protected:
	virtual void BeginPlay() override;
};

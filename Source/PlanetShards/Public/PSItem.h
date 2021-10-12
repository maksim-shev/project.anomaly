// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PSInteractInterface.h"
#include "PSTypes.h"
#include "PSItem.generated.h"

UCLASS(Abstract)
class PLANETSHARDS_API APSItem final : public AActor, public IPSInteractInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	FItemData ItemInfo;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Quantity;

	virtual void BeginPlay() override;
	// Sets default values for this actor's properties
	APSItem();

	virtual void OnInteract_Implementation(const AActor* Interacting) override;
};

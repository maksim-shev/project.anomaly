// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PSInfoMessage.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class PLANETSHARDS_API UPSInfoMessage final : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* Message;

	void ShowInfoMessage(FText MessageText);

private:
	FTimerDelegate InfoMessageTimerTimerDel;
	FTimerHandle InfoMessageTimerHandle;

	UFUNCTION(BlueprintCallable)
	static void RemoveInfoMessageWidget(UPSInfoMessage* InfoMessageWidget);
};

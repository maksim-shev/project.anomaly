// Fill out your copyright notice in the Description page of Project Settings.


#include "PSInfoMessage.h"
#include "Components/TextBlock.h"
#include "Blueprint/WidgetTree.h"


void UPSInfoMessage::ShowInfoMessage(const FText MessageText)
{
	Message->SetText(MessageText);
	this->AddToViewport();
	InfoMessageTimerTimerDel.BindUFunction(this, FName("RemoveInfoMessageWidget"), this);
	GetWorld()->GetTimerManager().SetTimer(InfoMessageTimerHandle, InfoMessageTimerTimerDel, 3, true);
}

void UPSInfoMessage::RemoveInfoMessageWidget(UPSInfoMessage* InfoMessageWidget)
{
	InfoMessageWidget->RemoveFromParent();
}

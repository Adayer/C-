// Fill out your copyright notice in the Description page of Project Settings.


#include "CarsGameInstance.h"
#include "Blueprint/UserWidget.h"
void UCarsGameInstance::OnStart()
{
  Super::OnStart();
  ChangeMenuWidget(StartingWidgetClass);
}
void UCarsGameInstance::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
  if (CurrentWidget != nullptr)
  {
    CurrentWidget->RemoveFromViewport();
    CurrentWidget = nullptr;
  }
  if (NewWidgetClass != nullptr)
  {
    CurrentWidget = CreateWidget<UUserWidget>(this, NewWidgetClass);
    if (CurrentWidget != nullptr)
    {
      CurrentWidget->AddToViewport();
    }
  }
}

void UCarsGameInstance::OnServerButtonClick(FString sPort)
{
}

void UCarsGameInstance::OnClientButtonClick(FString sIP, FString sPort)
{
}

void UCarsGameInstance::OnServerStartButtonClick()
{
}

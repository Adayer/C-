// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidget.h"

#include "ArrangeEditorUtilityWidget.generated.h"

/**
 * 
 */
UCLASS()
class UMBEDITORUTILITY_API UArrangeEditorUtilityWidget : public UEditorUtilityWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
		void Hello();
	
	UFUNCTION(BlueprintCallable)
		void Radial(float Radius, AActor* CenterActor);
	
};

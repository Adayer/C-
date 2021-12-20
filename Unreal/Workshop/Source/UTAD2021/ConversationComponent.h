// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ConversationComponent.generated.h"

class UConversationAsset;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UTAD2021_API UConversationComponent : public UActorComponent
{
	GENERATED_BODY()
public: 
	UConversationComponent();
protected:
	virtual void BeginPlay() override;
public:

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	UFUNCTION(BlueprintCallable, Category = "Conversation")
	void ShowLine();

	UFUNCTION(BlueprintCallable, Category = "Conversation")
	void AdvanceConversation();

private:
	UPROPERTY(VisibleInstanceOnly, Category="Conversation")
		int uCurrentLine = 0;
	
	UPROPERTY(EditAnywhere, Category="Conversation")
		const UConversationAsset* pConversation;
};
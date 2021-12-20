// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ConversationAsset.generated.h"

USTRUCT(BlueprintType)
struct UTAD2021_API FConversationLine
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Text;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FColor Color;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Duration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Offset;
};

/**
 * 
 */
UCLASS(BlueprintType)
class UTAD2021_API UConversationAsset : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Conversation")
		FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Conversation")
		TArray<FConversationLine> Lines;
};

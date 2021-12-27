// Fill out your copyright notice in the Description page of Project Settings.

	
#pragma once
#include "UTAD2021/ConversationAsset.h"
#include "AssetTypeActions_Base.h"

class UTAD2021EDITOR_API FConversationAssetAction : public FAssetTypeActions_Base
{
	UClass* GetSupportedClass() const override
	{
		return UConversationAsset::StaticClass();
	}
	FText GetName() const override
	{
		return FText::FromString(TEXT("Conversation"));
	}
	FColor GetTypeColor() const override
	{
		return FColor::Emerald;
	}
	uint32 GetCategories() override
	{
		return EAssetTypeCategories::UI | EAssetTypeCategories::Misc;
	}
	FText GetAssetDescription(const FAssetData& AssetData) const override
	{
		return FText::FromString(AssetData.AssetName.ToString() + TEXT(" es un Conversation Asset"));
	}

	virtual bool HasActions(const TArray<UObject*>& InObjects) const override
	{
		return true;
	}

};

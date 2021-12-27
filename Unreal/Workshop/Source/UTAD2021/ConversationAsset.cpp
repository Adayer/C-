// Fill out your copyright notice in the Description page of Project Settings.


#include "ConversationAsset.h"

void UConversationAsset::SwapLines()
{
	if (Lines.Num() < 2)
	{
		for (int indexSwap = 0; i < Lines.Num() / 2; ++i)
		{
			Lines.Swap(indexSwap, Lines.Num() - 1 - i);
		}
	}
}

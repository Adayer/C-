// Fill out your copyright notice in the Description page of Project Settings.


#include "ConversationComponent.h"
#include "ConversationAsset.h"

UConversationComponent::UConversationComponent() : uCurrentLine(0), pConversation(nullptr)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UConversationComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UConversationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UConversationComponent::AdvanceConversation()
{
	uCurrentLine += pConversation->Lines[uCurrentLine].Offset;
}

void UConversationComponent::ShowLine()
{
	if (pConversation == nullptr) { return; }
	if (uCurrentLine < 0 || uCurrentLine >= pConversation->Lines.Num()) { return; }

	FConversationLine const& Line = pConversation->Lines[uCurrentLine];
	GEngine->AddOnScreenDebugMessage(-1, Line.Duration, Line.Color, Line.Text);
}

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"

#include "MoveToEnemyBTTaskNode.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICA3_API UMoveToEnemyBTTaskNode : public UBTTaskNode
{
	GENERATED_BODY()
		
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual FString GetStaticDescription() const override;
protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

public:
	UMoveToEnemyBTTaskNode();
	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override {}
	
};

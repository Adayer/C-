// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "Camera/CameraActor.h"
#include "TimerManager.h"
#include "CamSwitchLevelScriptActor.generated.h"

/**
 *
 */
UCLASS()
class UNREALCPP_API ACamSwitchLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TArray<AActor*> LevelCameras;

public:
	void BeginPlay() override;

	UFUNCTION()
		void OnFirePressed();

	UFUNCTION(BlueprintCallable)
		void DoChangeCamera();

	UFUNCTION(BlueprintImplementableEvent)
		void ShowCameraName(ACameraActor* _camera);
	UFUNCTION(BlueprintNativeEvent)
		void LoopThroughCameras(float _timeLapse);
private:
	void ChangeCamera();
	int32 Counter;
	

};
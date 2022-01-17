// Fill out your copyright notice in the Description page of Project Settings.


#include "ArrangeEditorUtilityWidget.h"
#include "EditorLevelLibrary.h"

#define DEBUG_MSG(x, ...) if(GEngine) {GEngine ->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString::Printf(TEXT(x), __VA_ARGS__));}


void UArrangeEditorUtilityWidget::Hello()
{
	DEBUG_MSG("Hello %s", TEXT("World"));
}

void UArrangeEditorUtilityWidget::Radial(float Radius, AActor* CenterActor)
{
	if (CenterActor == nullptr)
	{
		return;
	}

	TArray<AActor*> Selection = UEditorLevelLibrary::GetSelectedLevelActors();
	int NumActors = Selection.Num();
	float RotationStep = 360.f / NumActors;
	FVector Center = CenterActor->GetActorLocation();

	int Index = 0;
	for (AActor* Actor : Selection)
	{
		if (Actor != CenterActor)
		{
			FVector RadiusVector(Radius, 0, 0);
			FRotator Rotation(0, Index * RotationStep, 0);
			RadiusVector = Rotation.RotateVector(RadiusVector);

			FTransform Transform(Rotation, Center + RadiusVector);
			Actor->SetActorTransform(Transform);
			++Index;
		}
	}

}

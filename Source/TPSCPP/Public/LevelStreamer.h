// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "LevelStreamer.generated.h"

UENUM()
enum ActionToDoEnum
{
	Load,
	Unload
};

/**
 * 
 */
UCLASS()
class TPSCPP_API ALevelStreamer : public ATriggerBox
{
	GENERATED_BODY()

public:
	ALevelStreamer();
	virtual void BeginPlay() override;

	void OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor);

	void LoadUnload(bool value);

	UPROPERTY(EditAnywhere)
	TEnumAsByte<ActionToDoEnum> ActionToDo;
	UPROPERTY(EditAnywhere)
	FName LayerToLoad;

private:
	UStaticMeshComponent* StaticMesh;
};

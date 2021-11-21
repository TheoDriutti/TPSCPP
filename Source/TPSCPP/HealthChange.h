// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TPSCPPCharacter.h"
#include "Components/BoxComponent.h"
#include "Engine/PointLight.h"
#include "GameFramework/Actor.h"
#include "HealthChange.generated.h"

UCLASS()
class TPSCPP_API AHealthChange : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	int healthChangeValue;

	// Sets default values for this actor's properties
	AHealthChange();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* Trigger;
	
	UFUNCTION()
	void OnBeginOverlap(AActor* OverlappedComponent, AActor* OtherActor);
	UFUNCTION()
	void OnEndOverlap(AActor* OverlappedComp, AActor* OtherActor);

	UFUNCTION()
	void ApplyChange();

private:
	float mCooldown = 1.f;
	bool mIsOverlapping = false;
	ATPSCPPCharacter* mCurrentOverlappingCharacter;
};

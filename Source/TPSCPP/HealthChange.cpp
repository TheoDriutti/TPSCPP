// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthChange.h"

#include <string>

#include "Components/BoxComponent.h"
#include "Engine/PointLight.h"
#include "GameFramework/Character.h"

#include "Engine/TriggerVolume.h"

// Sets default values
AHealthChange::AHealthChange()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	OnActorBeginOverlap.AddDynamic(this, &AHealthChange::OnBeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &AHealthChange::OnEndOverlap);
}

// Called when the game starts or when spawned
void AHealthChange::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AHealthChange::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (mIsOverlapping)
	{
		mCooldown -= DeltaTime;
		if (mCooldown <= 0.f)
		{
			mCooldown = 1.f;
			ApplyChange();
		}
	}
}

void AHealthChange::OnBeginOverlap(AActor* OverlappedComponent, AActor* OtherActor)
{
	ATPSCPPCharacter* Character = Cast<ATPSCPPCharacter>(OtherActor);
	if (Character == nullptr) return;

	if (!mIsOverlapping)
	{
		mCurrentOverlappingCharacter = Character;
		mIsOverlapping = true;
		mCooldown = 1.f;

		ApplyChange();
	}
}

void AHealthChange::OnEndOverlap(AActor* OverlappedComp, AActor* OtherActor)
{
	ATPSCPPCharacter* Character = Cast<ATPSCPPCharacter>(OtherActor);
	if (Character == nullptr) return;

	mCurrentOverlappingCharacter = nullptr;
	mIsOverlapping = false;
}

void AHealthChange::ApplyChange()
{
	int value = mCurrentOverlappingCharacter->GetHealth() + healthChangeValue;
	value = value < 0 ? 0 : (value > 100 ? 100 : value); // Clamp 0 - 100 

	mCurrentOverlappingCharacter->SetHealth(value);
}

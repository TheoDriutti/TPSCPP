// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelStreamer.h"

#include "Kismet/GameplayStatics.h"
#include "TPSCPP/TPSCPPCharacter.h"

ALevelStreamer::ALevelStreamer()
{
    PrimaryActorTick.bCanEverTick = true;
	
	OnActorBeginOverlap.AddDynamic(this, &ALevelStreamer::OnOverlapBegin);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("StaticMesh'/Game/Geometry/Meshes/1M_Cube.1M_Cube'"));
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	StaticMesh->SetCollisionProfileName(TEXT("Trigger"));
	if (CubeMesh.Succeeded())
	{
		StaticMesh->SetStaticMesh(CubeMesh.Object);
	}
	StaticMesh->SetSimulatePhysics(false);
    
	this->SetHidden(true);
}

void ALevelStreamer::BeginPlay()
{
	Super::BeginPlay();
    
}

void ALevelStreamer::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor)
{

	ATPSCPPCharacter* player = Cast<ATPSCPPCharacter>(OtherActor);
	if (player == nullptr)
	{
		return;
	}

	if(ActionToDo == ActionToDoEnum::Load)
	{
		LoadUnload(true);
	}
	else
	{
		LoadUnload(false);
	}
}

void ALevelStreamer::LoadUnload(bool Load)
{
	FLatentActionInfo LatentInfo;
	if(Load)
	{
		UGameplayStatics::LoadStreamLevel(this, LayerToLoad, true, false, LatentInfo);
		if(GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, ("LOAD " + LayerToLoad.ToString() ));
		}
	}
	else
	{
		UGameplayStatics::UnloadStreamLevel(this, LayerToLoad, LatentInfo, false);
		if(GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, ("UNLOAD " + LayerToLoad.ToString() ));
		}
	}
}
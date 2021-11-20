// Fill out your copyright notice in the Description page of Project Settings.


#include "TestJumpPad.h"
#include "GameFramework/Character.h"

// Sets default values
ATestJumpPad::ATestJumpPad()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeSM"));
	StaticMesh->SetSimulatePhysics(true);
	RootComponent = StaticMesh;

	StaticMesh->OnComponentHit.AddDynamic(this, &ATestJumpPad::OnHit);
}

// Called when the game starts or when spawned
void ATestJumpPad::BeginPlay()
{
	Super::BeginPlay();

	GLog->Log("bonjour");

}

// Called every frame
void ATestJumpPad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATestJumpPad::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, FVector NormalImpulse,
	const FHitResult& Hit) {

	ACharacter* Character = Cast<ACharacter>(OtherActor);
	if (Character == nullptr) {
		return;
	}
	Character->LaunchCharacter(FVector(0, 0, 1000), false, true);
}


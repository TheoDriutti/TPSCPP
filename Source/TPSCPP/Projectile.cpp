// Fill out your copyright notice in the Description page of Project Settings.

#define PrintString(String) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White,String)
#define printFString(text, fstring) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT(text), fstring))
#include "Engine/DecalActor.h"
#include "Components/DecalComponent.h"
#include "Projectile.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(
		TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("NomMesh"));
	if (SphereMesh.Succeeded()) StaticMesh->SetStaticMesh(SphereMesh.Object);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile"));
	ProjectileMovementComponent->OnProjectileStop.AddDynamic(this, &AProjectile::Hit);

	static ConstructorHelpers::FObjectFinder<UMaterial> Decal(TEXT("Material'/Game/Decal.Decal'"));
	if (Decal.Succeeded()) DecalMaterial = UMaterialInstanceDynamic::Create(Decal.Object, Decal.Object);

	// RootComponent = StaticMesh;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::Hit(const FHitResult& OutHit)
{
	PrintString("Hit");
	FRotator rotation = (OutHit.ImpactNormal * (-1.f)).XAxisVector.Rotation();
	ADecalActor* decal = GetWorld()->SpawnActor<ADecalActor>(OutHit.Location, rotation);
	decal->SetActorScale3D(decal->GetActorScale3D() * 0.3f);
	if (decal) decal->SetDecalMaterial(DecalMaterial);

	Destroy();
}

void AProjectile::SetVelocity(FVector direction)
{
	ProjectileMovementComponent->SetVelocityInLocalSpace(direction);
}

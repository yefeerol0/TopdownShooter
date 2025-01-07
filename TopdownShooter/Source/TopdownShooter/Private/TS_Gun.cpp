// Fill out your copyright notice in the Description page of Project Settings.


#include "TS_Gun.h"

// Sets default values
ATS_Gun::ATS_Gun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	GunMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gun Mesh"));
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	GunMesh->SetupAttachment(RootComponent);
}

void ATS_Gun::SpawnProjectile()
{
	GetWorld()->SpawnActor<ATS_Projectile>(ProjectileReference, GetActorLocation(), GetActorRotation());
}

// Called when the game starts or when spawned
void ATS_Gun::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATS_Gun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


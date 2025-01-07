// Fill out your copyright notice in the Description page of Project Settings.


#include "TS_Projectile.h"

// Sets default values
ATS_Projectile::ATS_Projectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	ProjectileMesh->SetupAttachment(RootComponent);

	ProjectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Component"));
	ProjectileComponent->InitialSpeed = 1000.0f;
	ProjectileComponent->ProjectileGravityScale = 0.0f;
}

// Called when the game starts or when spawned
void ATS_Projectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATS_Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


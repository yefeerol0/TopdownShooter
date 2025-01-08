// Fill out your copyright notice in the Description page of Project Settings.


#include "TS_Projectile.h"
#include "TS_Enemy.h"

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

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Collision Sphere"));
	CollisionSphere->SetupAttachment(ProjectileMesh);
}

void ATS_Projectile::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->IsA(ATS_Enemy::StaticClass()))
	{
		ATS_Enemy* Enemy = Cast<ATS_Enemy>(OtherActor);
		Enemy->TakeDamage();
	}
	Destroy();
}

void ATS_Projectile::BeginPlay()
{
	Super::BeginPlay();
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ATS_Projectile::BeginOverlap);
}

// Called every frame
void ATS_Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


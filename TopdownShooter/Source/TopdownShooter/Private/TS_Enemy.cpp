// Fill out your copyright notice in the Description page of Project Settings.


#include "TS_Enemy.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TS_Avatar.h"

ATS_Enemy::ATS_Enemy()
{
	Health = 30.0f;
	MaxHealth = 30.0f;
	WalkSpeed = 300.0f;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Collision Sphere"));
	CollisionSphere->SetupAttachment(RootComponent);
}

void ATS_Enemy::BeginPlay()
{
	Super::BeginPlay();
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ATS_Enemy::BeginOverlap);
}

void ATS_Enemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector PlayerLocation = GetPlayerLocation();
	FVector EnemyLocation = GetActorLocation();

	// Calculate direction to the player
	FVector Direction = (PlayerLocation - EnemyLocation).GetSafeNormal();

	// Update the enemy's location
	FVector NewLocation = EnemyLocation + Direction * WalkSpeed * DeltaTime;
	SetActorLocation(NewLocation);
}

void ATS_Enemy::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->IsA(ATS_Avatar::StaticClass()))
	{
		ATS_Avatar* Avatar = Cast<ATS_Avatar>(OtherActor);
		Avatar->TakeDamage();
	}
}

void ATS_Enemy::TakeDamage()
{
	Health -= 10.0f;

	if (Health <= 0)
	{
		Destroy();
	}
}

FVector ATS_Enemy::GetPlayerLocation() const
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (PlayerPawn)
	{
		return PlayerPawn->GetActorLocation();
	}
	else
	{
		return FVector::ZeroVector;
	}
}


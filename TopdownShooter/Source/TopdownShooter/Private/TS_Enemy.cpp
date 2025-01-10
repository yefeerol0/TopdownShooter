// Fill out your copyright notice in the Description page of Project Settings.


#include "TS_Enemy.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TS_Avatar.h"
#include "TS_Boss.h"

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

	FVector Direction = (PlayerLocation - EnemyLocation).GetSafeNormal();

	Direction.Z = 0.0f;
	Direction.Normalize();

	FVector NewLocation = EnemyLocation + Direction * WalkSpeed * DeltaTime;
	NewLocation.Z = EnemyLocation.Z; 
	SetActorLocation(NewLocation);

	FRotator NewRotation = Direction.Rotation();
	SetActorRotation(NewRotation);
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
		SpawnLootOnDeath();

		if (IsA(ATS_Boss::StaticClass()))
		{
			APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
			ATS_Avatar* Avatar = Cast<ATS_Avatar>(PlayerPawn);
			Avatar->Win();
		}

		DeathEffect();
		Destroy();
	
	}
}

void ATS_Enemy::SpawnLootOnDeath()
{
	int LootDropRatio = FMath::RandRange(1, 4);
	if (LootDropRatio == 4)
	{
		GetWorld()->SpawnActor<ATS_Lootbox>(LootboxReference, GetActorLocation(), GetActorRotation());
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


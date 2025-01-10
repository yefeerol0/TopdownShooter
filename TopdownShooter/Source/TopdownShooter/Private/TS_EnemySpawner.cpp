// Fill out your copyright notice in the Description page of Project Settings.


#include "TS_EnemySpawner.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATS_EnemySpawner::ATS_EnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpawnerLevel = ESpawnerLevel::NONE;
}

void ATS_EnemySpawner::Deactivate()
{
	Destroy();
}

void ATS_EnemySpawner::SpawnEnemyUnit()
{
	GetWorld()->SpawnActor<ATS_Enemy>(EnemyReference, GetActorLocation(), GetActorRotation());
	GWorld->GetTimerManager().SetTimer(SpawnTimerHandle, this, &ATS_EnemySpawner::TriggerSpawn, 1.0f, false);
}

void ATS_EnemySpawner::TriggerSpawn()
{
	uint8 LevelIndex = static_cast<uint8>(SpawnerLevel);
	SpawnRange = FMath::RandRange(10.0f - LevelIndex, 15.0f - LevelIndex);
	GWorld->GetTimerManager().SetTimer(SpawnUnitHandle, this, &ATS_EnemySpawner::SpawnEnemyUnit, SpawnRange, false);
}

void ATS_EnemySpawner::SpawnerEvolve()
{
	uint8 CurrentLevel = static_cast<uint8>(SpawnerLevel);
	uint8 MaxLevel = static_cast<uint8>(ESpawnerLevel::LEVEL_5);

	if (CurrentLevel < MaxLevel)
	{
		SpawnerLevel = static_cast<ESpawnerLevel>(CurrentLevel + 1);
	}
	GWorld->GetTimerManager().SetTimer(SpawnerEvolveHandle, this, &ATS_EnemySpawner::SpawnerEvolve, 30.0f, false);
}

// Called when the game starts or when spawned
void ATS_EnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	TriggerSpawn();
	GWorld->GetTimerManager().SetTimer(SpawnerEvolveHandle, this, &ATS_EnemySpawner::SpawnerEvolve, 30.0f, false);
}

// Called every frame
void ATS_EnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


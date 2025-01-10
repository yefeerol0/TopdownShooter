// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TS_Enemy.h"
#include "TS_EnemySpawner.generated.h"

UENUM(BlueprintType)
enum class ESpawnerLevel : uint8
{
	NONE = 0,
	LEVEL_1 = 1,
	LEVEL_2 = 2,
	LEVEL_3 = 3,
	LEVEL_4 = 4,
	LEVEL_5 = 5
};

UCLASS()
class ATS_EnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATS_EnemySpawner();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ESpawnerLevel SpawnerLevel;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ATS_Enemy> EnemyReference;

	UFUNCTION(BlueprintCallable)
	void Deactivate();

	FTimerHandle SpawnUnitHandle;
	void SpawnEnemyUnit();

	FTimerHandle SpawnTimerHandle;
	float SpawnRange;
	void TriggerSpawn();

	FTimerHandle SpawnerEvolveHandle;
	void SpawnerEvolve();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

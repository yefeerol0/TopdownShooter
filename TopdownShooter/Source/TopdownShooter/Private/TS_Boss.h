// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TS_Enemy.h"
#include "TS_Trap.h"
#include "TS_Avatar.h"
#include "TS_EnemySpawner.h"
#include "TS_Boss.generated.h"

/**
 * 
 */
UCLASS()
class ATS_Boss : public ATS_Enemy
{
	GENERATED_BODY()

	UFUNCTION()
	void DeactivateEnemySpawners();

	float SpawnRadius = 300.0f;
	FTimerHandle MoveCycleTimerHandle;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ATS_Enemy> EnemyReference;

	UFUNCTION()
	void SpawnEnemies();

	UFUNCTION()
	void BiggerTraps();

	UFUNCTION()
	void Regenerate();

	UFUNCTION()
	void CycleOfMoves();

	virtual void BeginPlay() override;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TS_Boss.h"
#include "GameFramework/GameModeBase.h"
#include "TS_GameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNSHOOTER_API ATS_GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Timer;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ATS_Boss> BossReference;

	UPROPERTY(EditAnywhere)
	FTransform BossSpawnPoint;

	FTimerHandle CountdownTimerHandle;
	FTimerHandle BossTimerHandle;

	virtual void BeginPlay() override;
	void Countdown();

	void BossSpawn();
	
};

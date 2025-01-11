// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TS_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNSHOOTER_API UTS_GameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CurrentDifficulty = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int HealthStatPlus = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int SpeedStatPlus = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CoinStatPlus = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int RemainingPoints = 10;
};

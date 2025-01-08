// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

	FTimerHandle CountdownTimerHandle;

	virtual void BeginPlay() override;
	void Countdown();
	
};

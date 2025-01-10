// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TS_Enemy.h"
#include "TS_Trap.h"
#include "TS_Boss.generated.h"

/**
 * 
 */
UCLASS()
class ATS_Boss : public ATS_Enemy
{
	GENERATED_BODY()

	virtual void BeginPlay() override;
};

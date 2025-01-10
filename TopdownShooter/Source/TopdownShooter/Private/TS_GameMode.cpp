// Fill out your copyright notice in the Description page of Project Settings.


#include "TS_GameMode.h"

void ATS_GameMode::BeginPlay()
{
	GWorld->GetTimerManager().SetTimer(CountdownTimerHandle, this, &ATS_GameMode::Countdown, 1.0f, false);
	GWorld->GetTimerManager().SetTimer(BossTimerHandle, this, &ATS_GameMode::BossSpawn, 300.0f, false);
}

void ATS_GameMode::Countdown()
{
	GWorld->GetTimerManager().SetTimer(CountdownTimerHandle, this, &ATS_GameMode::Countdown, 1.0f, false);
	Timer++;
}

void ATS_GameMode::BossSpawn()
{
	FVector BossSpawnLocation = BossSpawnPoint.GetLocation();
	FRotator BossSpawnRotation = BossSpawnPoint.GetRotation().Rotator();

	GetWorld()->SpawnActor<ATS_Boss>(BossReference, BossSpawnLocation, BossSpawnRotation);
}

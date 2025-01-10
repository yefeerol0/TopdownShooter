// Fill out your copyright notice in the Description page of Project Settings.


#include "TS_Boss.h"
#include "Kismet/GameplayStatics.h"

void ATS_Boss::DeactivateEnemySpawners()
{
    TArray<AActor*> FoundSpawners;

    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATS_EnemySpawner::StaticClass(), FoundSpawners);
    for (AActor* Spawner : FoundSpawners)
    {
        ATS_EnemySpawner* EnemySpawner = Cast<ATS_EnemySpawner>(Spawner);
        if (EnemySpawner)
        {
            EnemySpawner->Deactivate();
        }
    }
}

void ATS_Boss::SpawnEnemies()
{
    FVector BossLocation = GetActorLocation();

    TArray<FVector> SpawnOffsets = 
    {
        FVector(SpawnRadius, 0, -100),
        FVector(-SpawnRadius, 0, -100),
        FVector(0, SpawnRadius, -100),
        FVector(0, -SpawnRadius, -100)
    };

    for (const FVector& Offset : SpawnOffsets)
    {
        FVector SpawnLocation = BossLocation + Offset;
        FRotator SpawnRotation = FRotator::ZeroRotator;
        ATS_Enemy* SpawnedEnemy = GetWorld()->SpawnActor<ATS_Enemy>(EnemyReference, SpawnLocation, SpawnRotation);
    }
}

void ATS_Boss::BiggerTraps()
{
    TArray<AActor*> FoundTraps;

    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATS_Trap::StaticClass(), FoundTraps);
    for (AActor* Trap : FoundTraps)
    {
        ATS_Trap* BiggerTrap = Cast<ATS_Trap>(Trap);
        if (BiggerTrap)
        {
            BiggerTrap->SizeUp();
        }
    }
}

void ATS_Boss::Regenerate()
{
    if (Health + 200 <= MaxHealth)
    {
        Health += 200;
    }
    else 
    {
        Health = MaxHealth;

    }
}

void ATS_Boss::CycleOfMoves()
{
    int32 RandomChoice = FMath::RandRange(1, 3);

    switch (RandomChoice)
    {
    case 1:
        Regenerate();
        break;
    case 2:
        BiggerTraps();
        break;
    case 3:
        SpawnEnemies();
        break;
    default:
        break;
    }
}

void ATS_Boss::BeginPlay()
{
        Super::BeginPlay();
        APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
        ATS_Avatar* Avatar = Cast<ATS_Avatar>(PlayerPawn);

        Avatar->BossUI();
        Avatar->bBossUIAdded = true;

        DeactivateEnemySpawners();

        int RandomizeMoveTimes;
        GetWorld()->GetTimerManager().SetTimer(MoveCycleTimerHandle, this, &ATS_Boss::CycleOfMoves, RandomizeMoveTimes = FMath::RandRange(7.5f, 12.5f), true);

}

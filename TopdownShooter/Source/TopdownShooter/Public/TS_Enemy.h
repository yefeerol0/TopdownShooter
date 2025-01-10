// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TS_BaseCharacter.h"
#include "TS_Lootbox.h"
#include "Components/SphereComponent.h"
#include "TS_Enemy.generated.h"


UCLASS()
class TOPDOWNSHOOTER_API ATS_Enemy : public ATS_BaseCharacter
{
	GENERATED_BODY()

public:

	ATS_Enemy();

	UPROPERTY(EditAnywhere)
	USphereComponent* CollisionSphere;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ATS_Lootbox> LootboxReference;

	UFUNCTION(BlueprintImplementableEvent)
	void DeathEffect();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void BeginOverlap
	(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void TakeDamage();

	UFUNCTION()
	void SpawnLootOnDeath();

	UFUNCTION()
	FVector GetPlayerLocation() const;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TS_Projectile.h"
#include "TS_Gun.generated.h"

UCLASS()
class ATS_Gun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATS_Gun();


	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* GunMesh;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ATS_Projectile> ProjectileReference;

	void SpawnProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};

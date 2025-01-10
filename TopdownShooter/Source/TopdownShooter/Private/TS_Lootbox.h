// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Sound/SoundCue.h"
#include "TS_Lootbox.generated.h"

UENUM(BlueprintType)
enum class ELootboxType : uint8
{
	NONE = 0,
	COIN = 1,
	HEALTH = 2
};


UCLASS()
class ATS_Lootbox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATS_Lootbox();

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* LootboxMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ELootboxType LootboxType;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* CollisionSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterial* CoinMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterial* HealthMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundCue* HealSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundCue* CoinSound;

	UFUNCTION()
	void BeginOverlap
	(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "TS_Trap.generated.h"

UCLASS()
class ATS_Trap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATS_Trap();

	FTimerHandle TrapTriggerHandle;
	FTimerHandle TrapActivateHandle;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* TrapMesh;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* CollisionSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterial* OutlineMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterial* TrapMaterial;

	UFUNCTION()
	void BeginOverlap
	(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	bool bTrapActive;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void TrapSignalTrigger();
	void TrapReadyTrigger();

};

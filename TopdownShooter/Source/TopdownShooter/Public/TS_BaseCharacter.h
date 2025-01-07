// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TS_BaseCharacter.generated.h"

UCLASS()
class TOPDOWNSHOOTER_API ATS_BaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATS_BaseCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bDead;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Health;

	UPROPERTY(EditAnywhere)
	float MaxHealth;

	UPROPERTY(EditAnywhere)
	float WalkSpeed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

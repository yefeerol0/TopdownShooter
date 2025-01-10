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
	ATS_BaseCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
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

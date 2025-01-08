// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TS_BaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "TS_Gun.h"
#include "GameFrameWork/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TS_Avatar.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNSHOOTER_API ATS_Avatar : public ATS_BaseCharacter
{
	GENERATED_BODY()

public:
	
	ATS_Avatar();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, Category = "Character")
	TSubclassOf<ATS_Gun> GunType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	ATS_Gun* EquippedGun;

	UFUNCTION()
	void TakeDamage();

	UFUNCTION(BlueprintImplementableEvent)
	void Lose();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	void MoveForward(float value);
	void MoveRight(float value);
	void Shoot();
};

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

	FTimerHandle InvincibilityTimerHandle;
	UPROPERTY()
	bool bIsInvincible;

	UFUNCTION()
	void TakeDamage();

	UFUNCTION()
	void ResetInvincibility();

	UFUNCTION(BlueprintImplementableEvent)
	void Lose();

	UFUNCTION(BlueprintImplementableEvent)
	void Win();

	UFUNCTION(BlueprintImplementableEvent)
	void OpenShop();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int DashCharges = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanShoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int Coin;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bHealthUpgradeMax;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	ATS_Gun* SecondaryGun;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	bool bIsDashing; 
	FVector DashDirection; 
	float DashDistance;
	float DashDuration;
	int MaxDashCharges = 1;
	FTimerHandle DashTimerHandle;
	FTimerHandle DashCooldownHandle;
	FTimerHandle AutoShootHandle;

	void MoveForward(float value);
	void MoveRight(float value);
	void Shoot();
	void Dash();
	void StopDashing();
	void EnableDash();
	void StopShooting();

	// SHOP

	UFUNCTION(BlueprintCallable)
	void IncreaseMaxHealth();

	UFUNCTION(BlueprintCallable)
	void IncreaseMovementSpeed();

	UFUNCTION(BlueprintCallable)
	void GainDualWield();

	UFUNCTION(BlueprintCallable)
	void GainDoubleDash();

	UFUNCTION(BlueprintCallable)
	void GainAutoGuns();

	bool bDualWieldUnlocked;
	bool bDoubleDashUnlocked;
	bool bAutoGunsUnlocked;
	bool bHoldingShoot;
};

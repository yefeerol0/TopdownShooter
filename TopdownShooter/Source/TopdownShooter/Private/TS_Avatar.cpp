// Fill out your copyright notice in the Description page of Project Settings.


#include "TS_Avatar.h"
#include "Kismet/GameplayStatics.h"

ATS_Avatar::ATS_Avatar()
{

	Health = 100.0f;
	MaxHealth = 100.0f;
	Coin = 0;
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->TargetArmLength = 300.0f;
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	SpringArm->bUsePawnControlRotation = true;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

void ATS_Avatar::TakeDamage()
{
	if (!bIsInvincible)
	{
		Health -= 10.0f;

		if (Health <= 0)
		{
			APlayerController* PlayerController = Cast<APlayerController>(GetController());
			if (PlayerController)
			{
				PlayerController->CurrentMouseCursor = EMouseCursor::Default;
			}
			Lose();
		}

		bIsInvincible = true;
		GWorld->GetTimerManager().SetTimer(InvincibilityTimerHandle, this, &ATS_Avatar::ResetInvincibility, 1.5f, false);
	}
	else 
	{
		return;
	}
}

void ATS_Avatar::ResetInvincibility()
{
	bIsInvincible = false;
}

void ATS_Avatar::BeginPlay()
{
	Super::BeginPlay();

	bIsDashing = false;
	DashDistance = 1000.0f;
	DashDuration = 0.2f;

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		PlayerController->bShowMouseCursor = true;
		PlayerController->CurrentMouseCursor = EMouseCursor::Crosshairs;
	}

	if (GunType)
	{
		EquippedGun = GetWorld()->SpawnActor<ATS_Gun>(GunType);

		if (EquippedGun)
		{
			EquippedGun->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("GunSocket"));
			EquippedGun->SetOwner(this);
		}
	}
}

void ATS_Avatar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		FVector CursorWorldLocation, CursorWorldDirection;
		if (PlayerController->DeprojectMousePositionToWorld(CursorWorldLocation, CursorWorldDirection))
		{
			float DistanceToGround = (GetActorLocation().Z - CursorWorldLocation.Z) / CursorWorldDirection.Z;
			FVector GroundPoint = CursorWorldLocation + (CursorWorldDirection * DistanceToGround);
			FVector Direction = (GroundPoint - GetActorLocation()).GetSafeNormal();
			FRotator TargetRotation = Direction.Rotation();
			SetActorRotation(FRotator(0.f, TargetRotation.Yaw, 0.f));
		}
	}
}

void ATS_Avatar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ATS_Avatar::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATS_Avatar::MoveRight);

	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &ATS_Avatar::Shoot);
	PlayerInputComponent->BindAction("Shoot", IE_Released, this, &ATS_Avatar::StopShooting);
	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &ATS_Avatar::Dash);
	PlayerInputComponent->BindAction("Shop", IE_Pressed, this, &ATS_Avatar::OpenShop);
}

void ATS_Avatar::MoveForward(float value)
{
	FRotator Rotation = GetController()->GetControlRotation();
	FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
	FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(ForwardDirection, value);
}

void ATS_Avatar::MoveRight(float value)
{
	FRotator Rotation = GetController()->GetControlRotation();
	FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
	FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(RightDirection, value);
}

void ATS_Avatar::Shoot()
{
	bHoldingShoot = true;

	if (!bAutoGunsUnlocked)
	{
		if (bCanShoot && bDualWieldUnlocked)
		{
			EquippedGun->SpawnProjectile();
			SecondaryGun->SpawnProjectile();
			UGameplayStatics::PlaySoundAtLocation(this, ShootingSound, GetActorLocation());
		}
		else if (bCanShoot && !bDualWieldUnlocked)
		{
			EquippedGun->SpawnProjectile();
			UGameplayStatics::PlaySoundAtLocation(this, ShootingSound, GetActorLocation());
		}
	}
	else
	{
		if (bCanShoot && bDualWieldUnlocked && bHoldingShoot)
		{
			EquippedGun->SpawnProjectile();
			SecondaryGun->SpawnProjectile();
			GetWorld()->GetTimerManager().SetTimer(AutoShootHandle, this, &ATS_Avatar::Shoot, 0.2f, false);
			UGameplayStatics::PlaySoundAtLocation(this, ShootingSound, GetActorLocation());
		}
		else if (bCanShoot && !bDualWieldUnlocked && bHoldingShoot)
		{
			EquippedGun->SpawnProjectile();
			GetWorld()->GetTimerManager().SetTimer(AutoShootHandle, this, &ATS_Avatar::Shoot, 0.2f, false);
			UGameplayStatics::PlaySoundAtLocation(this, ShootingSound, GetActorLocation());
		}
		else if (!bHoldingShoot)
		{
			GetWorld()->GetTimerManager().ClearTimer(AutoShootHandle);
		}
	}
	
}

void ATS_Avatar::Dash()
{
	if (DashCharges <= 0 || bIsDashing)
	{
		return;
	}

	bIsDashing = true;
	DashCharges--;
	UGameplayStatics::PlaySoundAtLocation(this, DashSound, GetActorLocation());
	DashDirection = GetActorForwardVector();
	FVector DashVelocity = DashDirection * (DashDistance / DashDuration);
	LaunchCharacter(DashVelocity, true, true);
	GetWorld()->GetTimerManager().SetTimer(DashTimerHandle, this, &ATS_Avatar::StopDashing, DashDuration, false);

	if (DashCharges == 0)
	{
		GetWorld()->GetTimerManager().SetTimer(DashCooldownHandle, this, &ATS_Avatar::EnableDash, 5.0f, false);
	}
}

void ATS_Avatar::StopDashing()
{
	bIsDashing = false;
	GetCharacterMovement()->StopMovementImmediately();
}

void ATS_Avatar::EnableDash()
{
	DashCharges++;
	if (DashCharges < MaxDashCharges)
	{
		GetWorld()->GetTimerManager().SetTimer(DashCooldownHandle, this, &ATS_Avatar::EnableDash, 5.0f, false);
	}
}

void ATS_Avatar::StopShooting()
{
	bHoldingShoot = false;
	GetWorld()->GetTimerManager().ClearTimer(AutoShootHandle);
}

void ATS_Avatar::IncreaseMaxHealth()
{
	if (MaxHealth < 200 && Coin >= 10)
	{
		Coin -= 10;
		MaxHealth += 10.0f;
		Health += 10.0f;
		UGameplayStatics::PlaySoundAtLocation(this, BuySound, GetActorLocation());
	}
	else 
	{
		bHealthUpgradeMax = true;
	}
}

void ATS_Avatar::IncreaseMovementSpeed()
{
	if (GetCharacterMovement()->MaxWalkSpeed < 800 && Coin >= 10) 
	{
		Coin -= 10;
		GetCharacterMovement()->MaxWalkSpeed += 20.0f;
		UGameplayStatics::PlaySoundAtLocation(this, BuySound, GetActorLocation());
	}
}

void ATS_Avatar::GainDualWield()
{
	if (GunType && !bDualWieldUnlocked && Coin >= 50)
	{
		SecondaryGun = GetWorld()->SpawnActor<ATS_Gun>(GunType);

		if (SecondaryGun)
		{
			SecondaryGun->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("SecondaryGunSocket"));
			SecondaryGun->SetOwner(this);
			bDualWieldUnlocked = true;
			Coin -= 50;
			UGameplayStatics::PlaySoundAtLocation(this, BuySound, GetActorLocation());
		}
	}
}

void ATS_Avatar::GainDoubleDash()
{
	if (!bDoubleDashUnlocked && Coin >= 50)
	{
		DashCharges++;
		MaxDashCharges++;
		bDoubleDashUnlocked = true;
		Coin -= 50;
		UGameplayStatics::PlaySoundAtLocation(this, BuySound, GetActorLocation());
	}
}

void ATS_Avatar::GainAutoGuns()
{
	if (!bAutoGunsUnlocked && Coin >= 50)
	{
		bAutoGunsUnlocked = true;
		Coin -= 50;
		UGameplayStatics::PlaySoundAtLocation(this, BuySound, GetActorLocation());
	}
}

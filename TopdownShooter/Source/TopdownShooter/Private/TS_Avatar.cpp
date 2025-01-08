// Fill out your copyright notice in the Description page of Project Settings.


#include "TS_Avatar.h"

ATS_Avatar::ATS_Avatar()
{
	Health = 100.0f;
	MaxHealth = 100.0f;


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
}

void ATS_Avatar::BeginPlay()
{
	Super::BeginPlay();
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
	EquippedGun->SpawnProjectile();
}

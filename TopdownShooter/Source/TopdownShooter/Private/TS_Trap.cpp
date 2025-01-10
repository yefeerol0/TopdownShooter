// Fill out your copyright notice in the Description page of Project Settings.

#include "TS_Trap.h"
#include "TS_Avatar.h"


// Sets default values
ATS_Trap::ATS_Trap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TrapMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Trap Mesh"));
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	TrapMesh->SetupAttachment(RootComponent);

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Collision Sphere"));
	CollisionSphere->SetupAttachment(TrapMesh);
}

void ATS_Trap::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->IsA(ATS_Avatar::StaticClass()) && bTrapActive)
	{
		ATS_Avatar* Avatar = Cast<ATS_Avatar>(OtherActor);
		Avatar->TakeDamage();
	}
}

void ATS_Trap::SizeUp()
{
	FVector CurrentScale = TrapMesh->GetComponentScale();
	FVector NewScale = CurrentScale * 1.5f;               
	TrapMesh->SetWorldScale3D(NewScale);
}

void ATS_Trap::TrapSignalTrigger()
{
	TrapMesh->SetHiddenInGame(false);
	TrapMesh->SetMaterial(0, OutlineMaterial);
	GWorld->GetTimerManager().SetTimer(TrapActivateHandle, this, &ATS_Trap::TrapReadyTrigger, 5.0f, false);
}

void ATS_Trap::TrapReadyTrigger()
{
	TrapMesh->SetMaterial(0, TrapMaterial);
	bTrapActive = true;
}

// Called when the game starts or when spawned
void ATS_Trap::BeginPlay()
{
	Super::BeginPlay();
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ATS_Trap::BeginOverlap);
	TrapMesh->SetHiddenInGame(true);
	bTrapActive = false;

	int RandomTriggerTime = FMath::RandRange(15, 30);
	GWorld->GetTimerManager().SetTimer(TrapTriggerHandle, this, &ATS_Trap::TrapSignalTrigger, RandomTriggerTime, false);
}

// Called every frame
void ATS_Trap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


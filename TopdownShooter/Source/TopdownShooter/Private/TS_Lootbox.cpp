// Fill out your copyright notice in the Description page of Project Settings.


#include "TS_Lootbox.h"
#include "TS_Avatar.h"

// Sets default values
ATS_Lootbox::ATS_Lootbox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	LootboxType = ELootboxType::NONE;

	LootboxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Lootbox Mesh"));
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	LootboxMesh->SetupAttachment(RootComponent);

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Collision Sphere"));
	CollisionSphere->SetupAttachment(LootboxMesh);
}

void ATS_Lootbox::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->IsA(ATS_Avatar::StaticClass()))
	{
		ATS_Avatar* Avatar = Cast<ATS_Avatar>(OtherActor);
		if (LootboxType == ELootboxType::COIN)
		{
			int RandomCoin = FMath::RandRange(5, 10);
			Avatar->Coin += RandomCoin;
		}
		if (LootboxType == ELootboxType::HEALTH)
		{
			if (Avatar->Health <= Avatar->MaxHealth - 10)
			{
				Avatar->Health += 10;
			}
			else 
			{
				Avatar->Health = Avatar->MaxHealth;
			}
		}

		Destroy();
	}
}

// Called when the game starts or when spawned
void ATS_Lootbox::BeginPlay()
{
	Super::BeginPlay();

	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ATS_Lootbox::BeginOverlap);

	uint8 RandomValue = FMath::RandRange(1, 2);
	ELootboxType RandomLootboxType = static_cast<ELootboxType>(RandomValue);
	LootboxType = RandomLootboxType;

	switch (RandomLootboxType)
	{
	case ELootboxType::COIN:
		LootboxMesh->SetMaterial(0, CoinMaterial);
		break;
	case ELootboxType::HEALTH:
		LootboxMesh->SetMaterial(0, HealthMaterial);
		break;
	};
}

// Called every frame
void ATS_Lootbox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


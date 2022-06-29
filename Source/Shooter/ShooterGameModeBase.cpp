// Copyright Epic Games, Inc. All Rights Reserved.


#include "ShooterGameModeBase.h"
#include "MyPawn.h"
#include "ConditionComponent.h"
#include "Kismet/GameplayStatics.h"

AShooterGameModeBase::AShooterGameModeBase() :
	EnemyPointMultiplayer(1.0f)
{
	LvlManager = CreateDefaultSubobject<ULvlManager>(TEXT("LvlManager"));
	EnemySpawnComponent = CreateDefaultSubobject<UEnemySpawnComponent>(TEXT("EnemySpawnComponent"));
	PlayerHealth = CreateDefaultSubobject<UPlayerHealth>(TEXT("PlayerHealth"));
	Score = 0;
	Coins = 0;
	AddedCoins = 0;
}

void AShooterGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	PlayerHealth->OnHealthEnded.AddDynamic(this, &AShooterGameModeBase::EndGame);
}

void AShooterGameModeBase::AddScore(int DeltaScore)
{
	this->Score += DeltaScore * EnemyPointMultiplayer;
	if (LvlManager->isLvlEnd(Score))
	{
		LvlManager->LvlUp(EnemyPointMultiplayer, EnemySpawnComponent->EnemySpeedMultiplier);
	}
}

void AShooterGameModeBase::AddCoins(int DeltaCoins, bool isAddBonusCoins)
{
	this->Coins += DeltaCoins;
	if (isAddBonusCoins)
		this->Coins += AddedCoins;
}

int AShooterGameModeBase::GetScore()
{
	return this->Score;
}

int AShooterGameModeBase::GetCoins()
{
	return this->Coins;
}

void AShooterGameModeBase::EndGame() 
{
	AMyPawn* PlayerPawn = Cast<AMyPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (!PlayerPawn) return;
	EnemySpawnComponent->DestroyComponent();
	PlayerPawn->OnGameEnded();
	OnGameEnded.Broadcast();
}

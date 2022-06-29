// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EnemySpawnComponent.h"
#include "PlayerHealth.h"
#include "LvlManager.h"
#include "ShooterGameModeBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameEndedEvent);

UCLASS()
class SHOOTER_API AShooterGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	AShooterGameModeBase();

	virtual void BeginPlay() override;
private: 

	int Score;
	int Coins;

public:
	void AddScore(int DeltaScore);

	void AddCoins(int DeltaCoins, bool isAddBonusCoins = false);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStats")
	int AddedCoins;

	UFUNCTION(BlueprintCallable, Category = "Game")
	int GetScore();

	UFUNCTION(BlueprintCallable, Category = "Game")
	int GetCoins();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemies")
	UEnemySpawnComponent* EnemySpawnComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player")
	UPlayerHealth* PlayerHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LvlManager")
	ULvlManager* LvlManager;

	UFUNCTION(BlueprintCallable, Category = "Player")
	void EndGame();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
	float EnemyPointMultiplayer;

	UPROPERTY(BlueprintAssignable, Category = "Game")
	FGameEndedEvent OnGameEnded;
};

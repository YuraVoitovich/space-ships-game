// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyPawn.h"
#include "RangeCalculation.h"
#include "EnemySpawnComponent.generated.h"



USTRUCT(BlueprintType)
struct FEnemySpawnInfo
{
	GENERATED_BODY()

	FRangeCalculation SpawnBoxesRangeCalculation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AEnemyPawn> EnemyClass;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int NumOfEnemies;*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bRotateToPlayer = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int EnemySpawnChance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTransform SpawnTransform;

	FVector GetRandomLocation(TArray<FBox> FSpawnRanges)
	{
		return FMath::RandPointInBox(FSpawnRanges[SpawnBoxesRangeCalculation.GetRandomIndex()]);
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn ranges")
	TArray<int> SpawnBoxesPriorities;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn ranges")
	TArray<FBox> SpawnBoxesArray;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTER_API UEnemySpawnComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnemySpawnComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	void StartSpawnStage();
	FEnemySpawnInfo SpawnStage;
	FRandomStream Random;
	void SpawnEnemy();
	int EnemiesSpawnCounter;
	FTimerHandle ChangeStateTimer;
	FTimerHandle EnemySpawnTimer;
	FRangeCalculation SpawnEnemyRangeCalculation;

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
	TArray<FEnemySpawnInfo> SpawnStages;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
	float EnemySpeedMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
	float StageMinDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
	float StageMaxDelay;
		
};

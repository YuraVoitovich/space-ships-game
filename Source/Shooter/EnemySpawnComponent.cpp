// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawnComponent.h"
#include "TimerManager.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UEnemySpawnComponent::UEnemySpawnComponent()
{
	EnemySpeedMultiplier = 1.0;
}

// Called when the game starts
void UEnemySpawnComponent::BeginPlay()
{
	Super::BeginPlay();
	Random.GenerateNewSeed();
	for (int i = 0; i < SpawnStages.Num(); i++)
	{
		SpawnEnemyRangeCalculation.AddSpawnChancesArrayItem(SpawnStages[i].EnemySpawnChance);
		for (int j = 0; j < SpawnStages[i].SpawnBoxesPriorities.Num(); j++)
			SpawnStages[i].SpawnBoxesRangeCalculation.AddSpawnChancesArrayItem(SpawnStages[i].SpawnBoxesPriorities[j]);
		SpawnStages[i].SpawnBoxesRangeCalculation.FillSpawnEnemyRangeArray();
	}
	SpawnEnemyRangeCalculation.FillSpawnEnemyRangeArray();

	StartSpawnStage();
}

void UEnemySpawnComponent::StartSpawnStage()
{
	SpawnStage = SpawnStages[SpawnEnemyRangeCalculation.GetRandomIndex()];
	SpawnStage.SpawnTransform.SetLocation(SpawnStage.GetRandomLocation(SpawnStage.SpawnBoxesArray));
	if (SpawnStage.bRotateToPlayer) {
		SpawnStage.SpawnTransform.SetRotation(UKismetMathLibrary::FindLookAtRotation(SpawnStage.SpawnTransform.GetLocation(), UGameplayStatics::GetPlayerPawn(this, 0)->GetActorLocation()).Quaternion());
	}
	else {
		SpawnStage.SpawnTransform.SetRotation(UKismetMathLibrary::FindLookAtRotation(SpawnStage.SpawnTransform.GetLocation(), FVector(0.f, Random.FRandRange(-500.f, +500.f), 0.f)).Quaternion());
	}
	SpawnEnemy();

	GetWorld()->GetTimerManager().SetTimer(ChangeStateTimer, this, &UEnemySpawnComponent::StartSpawnStage, Random.FRandRange(StageMinDelay, StageMaxDelay), false, Random.FRandRange(StageMinDelay, StageMaxDelay));
}

void UEnemySpawnComponent::SpawnEnemy()
{
	FActorSpawnParameters SpawnParameters;
	AEnemyPawn* EnemyPawn = GetWorld()->SpawnActor<AEnemyPawn>(SpawnStage.EnemyClass, SpawnStage.SpawnTransform, SpawnParameters);
	EnemyPawn->MovementSpeed *= this->EnemySpeedMultiplier;
}

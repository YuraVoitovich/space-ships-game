// Fill out your copyright notice in the Description page of Project Settings.


#include "LvlManager.h"

// Sets default values for this component's properties
ULvlManager::ULvlManager()
{
	EnemyPointMultiplayerLvlChange = 0.1;
	EnemySpeedLvlChange = 0.1;
	Lvl = 0;
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void ULvlManager::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void ULvlManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool ULvlManager::isLvlEnd(int Score)
{
	return ScoreToLvl[this->Lvl] < Score;
}

int ULvlManager::getLvl()
{
	return this->Lvl;
}

void ULvlManager::LvlUp(float &ScoreMultiplayer, float &EnemySpeedMultiplayer)
{
	Lvl++;
	ScoreMultiplayer += EnemyPointMultiplayerLvlChange;
	EnemySpeedMultiplayer += EnemySpeedLvlChange;
}
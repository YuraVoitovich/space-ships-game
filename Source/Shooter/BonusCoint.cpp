// Fill out your copyright notice in the Description page of Project Settings.


#include "BonusCoint.h"
#include "ShooterGameModeBase.h"
#include "Kismet/GameplayStatics.h"

void ABonusCoint::ApplyBonus(AActor* TargetActor)
{
	AShooterGameModeBase* GameMode = Cast<AShooterGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	GameMode->AddCoins(Coins, true);
}

void ABonusCoint::BeginPlay()
{
	Super::BeginPlay();
}
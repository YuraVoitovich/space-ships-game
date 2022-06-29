// Fill out your copyright notice in the Description page of Project Settings.


#include "BonusShield.h"
#include "MyPawn.h"
void ABonusShield::ApplyBonus(AActor* TargetActor)
{
	AMyPawn *PlayerPawn = Cast<AMyPawn>(TargetActor);
	if (PlayerPawn == NULL) return;
	PlayerPawn->ActivateShield();
}

void ABonusShield::BeginPlay()
{
	Super::BeginPlay();
}
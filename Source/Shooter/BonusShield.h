// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BonusActor.h"
#include "BonusShield.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API ABonusShield : public ABonusActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void ApplyBonus(AActor* TargetActor) override;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LvlManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTER_API ULvlManager : public UActorComponent
{
	GENERATED_BODY()

private:
	int Lvl;

public:	
	// Sets default values for this component's properties
	ULvlManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool isLvlEnd(int Score);

	void LvlUp(float& ScoreMultiplayer, float& EnemySpeedMultiplayer);

	int getLvl();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
	float EnemyPointMultiplayerLvlChange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
	float EnemySpeedLvlChange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
	TArray<int> ScoreToLvl;

};

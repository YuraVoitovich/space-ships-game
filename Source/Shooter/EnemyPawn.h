// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ShootComponent.h"
#include "Components/BoxComponent.h"
#include "ConditionComponent.h"
#include "BonusActor.h"
#include "RangeCalculation.h"
#include "EnemyPawn.generated.h"

USTRUCT(BlueprintType)
struct FBonusInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ABonusActor> BonusClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int EnemySpawnChance;
};

UCLASS()
class SHOOTER_API AEnemyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemyPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void DestroyPawn();

	UFUNCTION()
	void OnEnemyOverlap(AActor* Actor, AActor* OtherActor);

	UFUNCTION(BlueprintCallable)
		bool IsInScreenRange();
	bool bWasInScreenRange;
	FRangeCalculation BonusRangeCalculation;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
		TArray<FBonusInfo> BonusArray;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn")
		UBoxComponent* PawnCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn")
		UShootComponent* ShootComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn")
		UStaticMeshComponent* PawnMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn")
		UConditionComponent* ConditionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SreenRange")
		float MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn")
		int PointsPerKill;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SreenRange")
		float LeftScreenRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SreenRange")
		float RightScreenRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SreenRange")
		float TopScreenRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SreenRange")
		float BottomScreenRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particle")
		UParticleSystem* DestroyParticle;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ShootProjectile.h"
#include "ShootComponent.generated.h"

USTRUCT(BlueprintType)
struct FShootingManagerInfo
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controls")
		TSubclassOf<AShootProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector Offset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Angle;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTER_API UShootComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UShootComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	FTimerHandle ShootingTimer;

	void Shoot();


public:	

	UFUNCTION(BlueprintCallable, Category = "Shooting")
	void StartShooting();

	UFUNCTION(BlueprintCallable, Category = "Shooting")
	void StopShooting();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controls")
	float ShootDelay;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controls")
	TArray<FShootingManagerInfo> ShootingInfos;
};

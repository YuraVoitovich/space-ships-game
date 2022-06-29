// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "BonusActor.generated.h"

UCLASS()
class SHOOTER_API ABonusActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABonusActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void BonusDestroy();
	UFUNCTION()
	void OnActorOverlap(AActor* Actor, AActor* OtherActor);
	UFUNCTION()
	virtual void ApplyBonus(AActor* TargetActor);
	FTimerHandle LifeTimeTimer;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
		UBoxComponent* BonusCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
		UStaticMeshComponent* BonusMesh;
};

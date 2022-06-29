// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerHealth.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerHealthEndedEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerHealthChangedEvent, int, ChangeValue);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTER_API UPlayerHealth : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPlayerHealth();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnPlayerDamaged(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* Instigator, AActor* DamageCouser);

	int Healths = 3;
public:

	UFUNCTION(BlueprintCallable, Category = "Player Health")
	void ChangeHealths(int Value);

	UFUNCTION(BlueprintPure, Category = "Player Health")
	int GetHealths();

	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnPlayerHealthEndedEvent OnHealthEnded;

	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnPlayerHealthChangedEvent OnHealthChanged;
};

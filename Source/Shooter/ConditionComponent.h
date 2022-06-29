// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ConditionComponent.generated.h"

// Event dispatcher macros
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHealthEndedEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTER_API UConditionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UConditionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Health
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float Health;

	// OnTakeAnyDamage event
	UFUNCTION()
		void OnOwnerDamaged(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* Instigator, AActor* DamageCouser);

public:	
	UFUNCTION(BlueprintCallable, Category = "Health")
		void ChangeHealth(float Value);

	UFUNCTION(BlueprintPure, Category = "Health")
		float GetHealth();

	// Event of FHealthEndedEvent dispatcher
	UPROPERTY(BlueprintAssignable, Category = "Health")
		FHealthEndedEvent OnHealthEnded;
};

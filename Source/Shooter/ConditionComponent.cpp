// Fill out your copyright notice in the Description page of Project Settings.


#include "ConditionComponent.h"

// Sets default values for this component's properties
UConditionComponent::UConditionComponent() :
	Health(100) // Default Health
{
}


// Called when the game starts
void UConditionComponent::BeginPlay()
{
	Super::BeginPlay();
	
	// Bind event on take any damage 
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UConditionComponent::OnOwnerDamaged);
}

// OnTakeAnyDamage event
void UConditionComponent::OnOwnerDamaged(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* Instigator, AActor* DamageCouser)
{
	ChangeHealth(-Damage);
}

void UConditionComponent::ChangeHealth(float Value)
{
	Health += Value;
	if (Health <= 0) {
		// Remove binded event on take any damage
		GetOwner()->OnTakeAnyDamage.RemoveDynamic(this, &UConditionComponent::OnOwnerDamaged);

		// Call events, that binded OnHealthEnded. (Refers: EnemyPawn.cpp) 
		OnHealthEnded.Broadcast();
	}
}

float UConditionComponent::GetHealth()
{
	return Health;
}


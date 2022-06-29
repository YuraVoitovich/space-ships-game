// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHealth.h"
#include "ShooterGameModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UPlayerHealth::UPlayerHealth() :
	Healths(3)
{
}

// Called when the game starts
void UPlayerHealth::BeginPlay()
{
	Super::BeginPlay();	
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	if (!PlayerPawn) return;
	PlayerPawn->OnTakeAnyDamage.AddDynamic(this, &UPlayerHealth::OnPlayerDamaged);
}

void UPlayerHealth::OnPlayerDamaged(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* Instigator, AActor* DamageCouser)
{
	ChangeHealths(-1);
}

void UPlayerHealth::ChangeHealths(int Value)
{
	Healths += Value;
	OnHealthChanged.Broadcast(Value);
	if (Healths <= 0) {
		OnHealthEnded.Broadcast();
	}
}

int UPlayerHealth::GetHealths()
{
	return Healths;
}



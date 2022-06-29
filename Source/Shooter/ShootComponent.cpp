// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"

// Sets default values for this component's properties
UShootComponent::UShootComponent()
{
	
}


// Called when the game starts
void UShootComponent::StopShooting()
{
	// clear timer
	GetWorld()->GetTimerManager().ClearTimer(ShootingTimer);
}

void UShootComponent::BeginPlay()
{
	StartShooting();
}

void UShootComponent::Shoot()
{
	for (FShootingManagerInfo ShootInfo : ShootingInfos) {
		// Get owner rotation 
		FRotator SpawnRotation = GetOwner()->GetActorRotation();
		// Get owner location and add to it offset  
		FVector SpawnLocation = SpawnRotation.RotateVector(ShootInfo.Offset) + GetOwner()->GetActorLocation();

		// Add to spawn rotation angel
		SpawnRotation.Add(0.f, ShootInfo.Angle, 0.f);

		FActorSpawnParameters SpawnParametrs;
	
		SpawnParametrs.Owner = GetOwner();
		// Spawn projectile
		AShootProjectile* ShootProjectile = GetWorld()->SpawnActor<AShootProjectile>(ShootInfo.ProjectileClass, SpawnLocation, SpawnRotation, SpawnParametrs);
		if (ShootProjectile) {
			if (ShootInfo.Speed != 0.0f)
				ShootProjectile->ProjectileSpeed = ShootInfo.Speed;
			ShootProjectile->ProjectileDamage = ShootInfo.Damage;
		}
	}
}

void UShootComponent::StartShooting()
{
	GetWorld()->GetTimerManager().SetTimer(ShootingTimer, this, &UShootComponent::Shoot, ShootDelay, true, ShootDelay);
}




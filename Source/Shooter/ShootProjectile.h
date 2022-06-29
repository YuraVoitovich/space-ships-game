// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "ShootProjectile.generated.h"

UCLASS()
class SHOOTER_API AShootProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShootProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnProjectileOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 BodyIndex, bool Sweep, const FHitResult& HitResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// collision components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shooting")
		USphereComponent* Collision;

	// mesh component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shooting")
		UStaticMeshComponent* Mesh;

	// speed of projectile
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
		float ProjectileSpeed;

	// projectile damage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
		float ProjectileDamage;
};

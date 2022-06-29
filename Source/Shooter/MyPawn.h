// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
#include "ShootComponent.h"
#include "ShooterGameModeBase.h"
#include "MyPawn.generated.h"

UCLASS()
class SHOOTER_API AMyPawn : public APawn
{
	GENERATED_BODY()
	

public:
	// Sets default values for this pawn's properties
	AMyPawn();

	void ActivateShield(float ShieldDuaration = 3.f);
	
protected:
	// Called when the game starts or when spawned

	virtual void BeginPlay() override;

	void DestroyShield();
	void ActivateShieldFlicker();
	void ShieldFlicker();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controls")
		float LeftScreenRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controls")
		float RightScreenRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controls")
		float TopScreenRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controls")
		float BottomScreenRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controls")
		float MovementSpeed;

	void OnTouchPress(ETouchIndex::Type Index, FVector TouchLocation);
	void OnTouchMove(ETouchIndex::Type Index, FVector TouchLocation);

	FTimerHandle ShootingTimer, MeshVisibilityTimer, ShieldFlickerTimer, ShieldTimer, StartShieldFlickerTimer;
	FVector2D TouchCoords;
	bool bFlipFlop;

	UFUNCTION()
		void SetMeshVisibility();

	UFUNCTION()
		virtual float TakeDamage
		(
			float DamageAmount,
			struct FDamageEvent const& DamageEvent,
			AController* EventInstigator,
			AActor* DamageCauser
		) override;

	UFUNCTION()
		void BeDamaged();
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void OnGameEnded();
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	APlayerController* PlayerController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn")
		UBoxComponent* PawnCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn")
		UShootComponent* ShootComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn")
		UStaticMeshComponent* PawnMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn")
		UStaticMeshComponent* ShieldMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn")
		UCameraComponent* CameraComponent;
	
};

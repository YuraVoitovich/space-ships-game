// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Pawn collision initialization 
	PawnCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("PawnCollision"));
	RootComponent = PawnCollision;

	// Pawn mesh initialization
	PawnMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PawnMesh"));
	PawnMesh->SetupAttachment(RootComponent);

	// Camera intialization
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetRelativeLocation(FVector(-100.f, 0.f, 1000.f));
	CameraComponent->SetRelativeRotation(FRotator(-80.f, 0.f, 0.f));

	// Shield mesh initialization
	ShieldMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShieldMesh"));
	ShieldMesh->SetupAttachment(RootComponent);
	ShieldMesh->SetVisibility(false);

	// Shoot conponent intialization
	ShootComponent = CreateDefaultSubobject<UShootComponent>(TEXT("ShootComponent"));

	// Screen borders
	LeftScreenRange = -500.f;
	RightScreenRange = 500.f;
	BottomScreenRange = -500.f;
	TopScreenRange = 500.f;

	// MovementSpeed
	MovementSpeed = 1.0f;
}

void AMyPawn::ActivateShield(float ShieldDuaration)
{
	float fDeltaTime = ShieldDuaration - 1.f;
	fDeltaTime = fDeltaTime > 0.f ? fDeltaTime : 0.f;
	ShieldMesh->SetVisibility(true);
	SetCanBeDamaged(false);
	GetWorld()->GetTimerManager().SetTimer(StartShieldFlickerTimer, this, &AMyPawn::ActivateShieldFlicker, 0.2f, false, fDeltaTime);
	GetWorld()->GetTimerManager().SetTimer(ShieldTimer, this, &AMyPawn::DestroyShield, 0.2f, false, ShieldDuaration);
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	//OnTakeAnyDamage.AddDynamic(this, &AMyPawn::OnDamaged);
	PlayerController = Cast<APlayerController>(GetController());
	//ConditionComponent->OnHealthEnded.AddDynamic(this, &AEnemyPawn::DestroyPawn);
}

void AMyPawn::DestroyShield()
{
	GetWorld()->GetTimerManager().ClearTimer(ShieldFlickerTimer);
	ShieldMesh->SetVisibility(false);
	SetCanBeDamaged(true);
}

void AMyPawn::ActivateShieldFlicker()
{
	bFlipFlop = false;
	GetWorld()->GetTimerManager().SetTimer(ShieldFlickerTimer, this, &AMyPawn::ShieldFlicker, 0.2f, true, 0.2f);
}

void AMyPawn::ShieldFlicker()
{
	ShieldMesh->SetVisibility(bFlipFlop);
	bFlipFlop = !bFlipFlop;
}

float AMyPawn::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (CanBeDamaged()) {
		Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
		ShootComponent->StopShooting();
		SetCanBeDamaged(false);
		bFlipFlop = false;
		GetWorld()->GetTimerManager().SetTimer(MeshVisibilityTimer, this, &AMyPawn::SetMeshVisibility, 0.2f, true, 0.3f);
		GetWorld()->GetTimerManager().SetTimer(ShootingTimer, this, &AMyPawn::BeDamaged, 3.f, false, 3.f);
		return DamageAmount;
	} 
	return 0.0f;
}

void AMyPawn::SetMeshVisibility()
{
	PawnMesh->SetVisibility(bFlipFlop);
	bFlipFlop = !bFlipFlop;
}

void AMyPawn::BeDamaged()
{
	ShootComponent->StartShooting();
	SetCanBeDamaged(true);
	PawnMesh->SetVisibility(true);
	GetWorld()->GetTimerManager().ClearTimer(MeshVisibilityTimer);
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	bool bTouched;
	float TouchX, TouchY;
	PlayerController->GetInputTouchState(ETouchIndex::Touch1, TouchX, TouchY, bTouched);

	if (bTouched) {
		FVector2D TouchDeltaMove = FVector2D(TouchCoords.X - TouchX, TouchCoords.Y - TouchY);
		AddActorLocalOffset(FVector(TouchDeltaMove.Y * -1.f, TouchDeltaMove.X, 0.0f));
		TouchCoords = FVector2D(TouchX, TouchY);
	}
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindTouch(IE_Pressed, this, &AMyPawn::OnTouchPress);
	InputComponent->BindTouch(IE_Repeat, this, &AMyPawn::OnTouchMove);
}

void AMyPawn::OnTouchMove(ETouchIndex::Type Index, FVector TouchLocation) 
{
	FVector2D TouchDeltaMove = FVector2D(TouchCoords.X - TouchLocation.X, TouchCoords.Y - TouchLocation.Y);
	TouchDeltaMove *= MovementSpeed;
	FVector NewLocation = GetActorLocation();
	NewLocation.X = FMath::Clamp(NewLocation.X + TouchDeltaMove.Y, BottomScreenRange, TopScreenRange);
	NewLocation.Y = FMath::Clamp(NewLocation.Y + TouchDeltaMove.X * -1.f, LeftScreenRange, RightScreenRange);
	SetActorLocation(NewLocation);
	TouchCoords = FVector2D(TouchLocation.X, TouchLocation.Y);
}

void AMyPawn::OnGameEnded()
{
	this->Destroy();
}

void AMyPawn::OnTouchPress(ETouchIndex::Type Index, FVector TouchLocation)
{
	TouchCoords = FVector2D(TouchLocation.X, TouchLocation.Y);
}




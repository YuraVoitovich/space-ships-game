// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyPawn.h"
#include "ShooterGameModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemyPawn::AEnemyPawn()
	:
	MovementSpeed(5.f),
	PointsPerKill(10)
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create collision with "Pawn" profile name 
	PawnCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("PawnCollision"));
	RootComponent = PawnCollision;
	PawnCollision->SetCollisionProfileName("Pawn");
	
	bWasInScreenRange = false;
	// Create mesh without collision 
	PawnMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PawnMesh"));
	PawnMesh->SetupAttachment(RootComponent);
	PawnMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Create shoot component
	ShootComponent = CreateDefaultSubobject<UShootComponent>(TEXT("ShootComponent"));

	// Create condition component
	ConditionComponent = CreateDefaultSubobject<UConditionComponent>(TEXT("ConditionComponent"));

	bWasInScreenRange = false;
	LeftScreenRange = -1500.f;
	RightScreenRange = 1500.f;
	BottomScreenRange = -800.f;
	TopScreenRange = 1500.f;
}

// Called when the game starts or when spawned
void AEnemyPawn::BeginPlay()
{
	Super::BeginPlay();
	
	for (auto it : BonusArray) {
		BonusRangeCalculation.AddSpawnChancesArrayItem(it.EnemySpawnChance);
	}
	BonusRangeCalculation.FillSpawnEnemyRangeArray();

	// Bind event on OnHealthEnded (broadcasts in ConditionComponent.cpp)
	ConditionComponent->OnHealthEnded.AddDynamic(this, &AEnemyPawn::DestroyPawn);
	Cast<AShooterGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->PlayerHealth->OnHealthEnded.AddDynamic(this, &AEnemyPawn::DestroyPawn);
	OnActorBeginOverlap.AddDynamic(this, &AEnemyPawn::OnEnemyOverlap);
}

void AEnemyPawn::OnEnemyOverlap(AActor* Actor, AActor* OtherActor)
{
	// if overlaped actor is't Player
	if (OtherActor != UGameplayStatics::GetPlayerPawn(this, 0)) return;

	// Checking can the Player be damaged
	if (OtherActor->CanBeDamaged()) 
	{
		// Apply damage to Player
		UGameplayStatics::ApplyDamage(OtherActor, 100, GetController(), this, UDamageType::StaticClass());

		// Call overlaped actor reaction
		DestroyPawn();
	}
}

bool AEnemyPawn::IsInScreenRange()
{
	FVector Location = GetActorLocation();
	bool bIsInScreenRange = (Location.Y > LeftScreenRange)
		&& (Location.Y < RightScreenRange)
		&& (Location.X > BottomScreenRange)
		&& (Location.X < TopScreenRange);

	if (bIsInScreenRange)
		bWasInScreenRange = true;
	else
		if (bWasInScreenRange && !bIsInScreenRange)
			return false;
	return true;
}

void AEnemyPawn::DestroyPawn()
{
	AShooterGameModeBase* GameMode = Cast<AShooterGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	GameMode->AddScore(this->PointsPerKill);
	int Index = BonusRangeCalculation.GetRandomIndex();
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	ABonusActor* BonusActor;
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DestroyParticle, this->GetActorTransform());
	if (Index != -1)
	{
		BonusActor = GetWorld()->SpawnActor<ABonusActor>(BonusArray[Index].BonusClass, this->GetTransform(), SpawnParameters);
	}
	Destroy();
}

// Called every frame
void AEnemyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsInScreenRange())
	{
		Destroy();
	}

	AddActorLocalOffset(FVector(this->MovementSpeed, 0.f, 0.f));
	// Enemy movement
	
	
}


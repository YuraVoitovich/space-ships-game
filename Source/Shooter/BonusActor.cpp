// Fill out your copyright notice in the Description page of Project Settings.


#include "BonusActor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABonusActor::ABonusActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BonusCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	RootComponent = BonusCollision;
	BonusMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	BonusMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABonusActor::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &ABonusActor::OnActorOverlap);
	
	GetWorld()->GetTimerManager().SetTimer(LifeTimeTimer, this, &ABonusActor::BonusDestroy, 3.0f, false, 3.0f);
}

void ABonusActor::OnActorOverlap(AActor* Actor, AActor* OtherActor)
{
	if (OtherActor != UGameplayStatics::GetPlayerPawn(this, 0)) return;
	
	if (OtherActor->CanBeDamaged())
	{
		ApplyBonus(OtherActor);
		BonusDestroy();
	}
}

void ABonusActor::ApplyBonus(AActor* TargetActor)
{
}

void ABonusActor::BonusDestroy()
{
	this->Destroy();
}

// Called every frame
void ABonusActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//this->AddActorLocalRotation(FQuat(0.f, 0.f, 1.f * DeltaTime, 0.f));
}


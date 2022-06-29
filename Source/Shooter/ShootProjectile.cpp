// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "BonusActor.h"
#include "GameFramework/Pawn.h"

// Sets default values
AShootProjectile::AShootProjectile() :
	ProjectileSpeed(100.f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set sphere collision
	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	RootComponent = Collision;
	Collision->SetCollisionResponseToAllChannels(ECR_Ignore);
	Collision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	// Set Projectile Mesh 
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collision, NAME_None);
	Mesh->SetCollisionProfileName("NoCollision");
}

// Called when the game starts or when spawned
void AShootProjectile::BeginPlay()
{
	Super::BeginPlay();
	if (GetOwner()) 
	{
		Collision->IgnoreActorWhenMoving(GetOwner(), true);
	}
	Collision->OnComponentBeginOverlap.AddDynamic(this, &AShootProjectile::OnProjectileOverlap);
}

void AShootProjectile::OnProjectileOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 BodyIndex, bool Sweep, const FHitResult& HitResult)
{
	//UE_LOG(LogTemp, Log, TEXT("Shooted ")); 
	if (Cast<ABonusActor>(OtherActor)) return;
	if (!GetOwner()) return;
	APawn* PawnOwner = Cast<APawn>(GetOwner());
	if (!PawnOwner) return;
	AController* Instig = PawnOwner->GetController();
	//UE_LOG(LogTemp, Log, TEXT("Damage: %f "), ProjectileDamage);
	UGameplayStatics::ApplyDamage(OtherActor, ProjectileDamage, Instig, this, UDamageType::StaticClass());

	Destroy();
}

// Called every frame
void AShootProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// Move projectile
	AddActorLocalOffset(FVector(ProjectileSpeed * DeltaTime, 0.f, 0.f));
}


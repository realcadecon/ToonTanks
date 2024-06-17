// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"

#include "Projectile.h"
#include "Kismet/GameplayStatics.h"

ATurret::ATurret()
{
}

void ATurret::BeginPlay()
{
	Super::BeginPlay();
	Target = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	TurretRange = 1000;
	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATurret::CheckFireCondition, FireRate, true);
}


// Called every frame
void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (InFireRange())
	{
		RotateTurret(Target->GetActorLocation());
	}
}

void ATurret::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}


void ATurret::CheckFireCondition()
{
	if (InFireRange())
	{
		AProjectile* SpawnedProjectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileClass,
			ProjectileSpawnPoint->GetComponentLocation(),
			ProjectileSpawnPoint->GetComponentRotation()
		);
		SpawnedProjectile->SetOwner(this);
	}
}

bool ATurret::InFireRange()
{
	return Target && FVector::Dist(Target->GetActorLocation(), GetActorLocation()) <= TurretRange;
}



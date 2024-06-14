// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"

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


void ATurret::CheckFireCondition()
{
	if (InFireRange())
	{
		DrawDebugSphere(
			GetWorld(),
			ProjectileSpawnPoint->GetComponentLocation(),
			10,
			10,
			FColor::Red,
			true,
			2.f
		);
	}
}

bool ATurret::InFireRange()
{
	return Target && FVector::Dist(Target->GetActorLocation(), GetActorLocation()) <= TurretRange;
}



// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"

#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));
	RootComponent = CapsuleComponent;

	BaseComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tank Base"));
	BaseComponent->SetupAttachment(CapsuleComponent);

	TurretComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret"));
	TurretComponent->SetupAttachment(BaseComponent);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretComponent);

}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABasePawn::RotateTurret(const FVector &Target)
{
	FVector ToTarget = Target - TurretComponent->GetComponentLocation();
	FRotator ToTargetRotation(0, ToTarget.Rotation().Yaw, 0);
	
	TurretComponent->SetWorldRotation(
		FMath::RInterpTo(TurretComponent->GetComponentRotation(),
		ToTargetRotation,
		UGameplayStatics::GetWorldDeltaSeconds(this),
		5.f)
	);
}



// Called to bind functionality to input
void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}




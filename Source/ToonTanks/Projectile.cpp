// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "LegacyCameraShake.h"

// Sets default values
AProjectile::AProjectile()
{
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh;
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(
		TEXT("Projectile Movement Component"));
	ProjectileMovementComponent->InitialSpeed = 1000.f;
	ProjectileMovementComponent->MaxSpeed = 2000.f;

	ProjectileTrailParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Projectile Trail Particles"));
	ProjectileTrailParticleSystemComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	
	if(LaunchSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation(), GetActorRotation());
	}
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                        FVector NormalImpulse, const FHitResult& Hit)
{
	const auto MyOwner = GetOwner();
	if (!MyOwner)
	{
		Destroy();
		return;
	}
	if(HitSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, HitSound, Hit.ImpactPoint, OtherActor->GetActorRotation());
	}
	if(CameraShakeClass)
	{
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(CameraShakeClass);
	}
	
	auto MyOwnerInstigator = MyOwner->GetInstigatorController();
	auto DamageTypeClass = UDamageType::StaticClass();
	if (OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwnerInstigator, this, DamageTypeClass);
		if (HitParticles)
		{
			UGameplayStatics::SpawnEmitterAtLocation(
				this,
				HitParticles,
				GetActorLocation(),
				GetActorRotation()
			);
		}
	}
	Destroy();
}

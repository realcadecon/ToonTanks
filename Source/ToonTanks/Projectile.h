// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = Projectile)
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(EditAnywhere, Category = Projectile)
	UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditAnywhere, Category = Combat)
	UParticleSystemComponent* ProjectileTrailParticleSystemComponent;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere)
	float Damage = 50.f;

	UPROPERTY(EditAnywhere, Category = Combat)
	UParticleSystem* HitParticles;

	UPROPERTY(EditAnywhere, Category = SoundEffects)
	USoundBase* LaunchSound;

	UPROPERTY(EditAnywhere, Category = SoundEffects)
	USoundBase* HitSound;
	
	UPROPERTY(EditAnywhere, Category = CameraEffects)
	TSubclassOf<class ULegacyCameraShake> CameraShakeClass;
	
};

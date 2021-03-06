// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerProjectile.generated.h"

UCLASS()
class SUPERSIDESCROLLER_API APlayerProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APlayerProjectile();

	// sphere collision component
	UPROPERTY(VisibleDefaultsOnly, Category=Projectile)
	class USphereComponent* CollisionComp;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse,
	           const FHitResult& Hit);
	void ExplodeProjectile();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UParticleSystem* DestroyEffect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class USoundBase* DestroySound;

private:
	// projectile movement component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Movement, meta=(AllowPrivateAccess="true"))
	class UProjectileMovementComponent* ProjectileMovement;

	// static mesh component
	UPROPERTY(VisibleDefaultsOnly, Category=Projectile)
	class UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleDefaultsOnly, Category=Sound)
	class UAudioComponent* ProjectileMovementSound;

	UPROPERTY(VisibleDefaultsOnly, Category=Projectile)
	class UParticleSystemComponent* ProjectileEffect;
};

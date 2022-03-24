// Fill out your copyright notice in the Description page of Project Settings.


#include "SuperSideScroller_Player.h"
#include "SuperSideScroller.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimInstance.h"
#include "PlayerProjectile.h"
#include "Engine/World.h"
#include "Components/SphereComponent.h"

ASuperSideScroller_Player::ASuperSideScroller_Player()
{
	bIsSprinting = false;
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
}

void ASuperSideScroller_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ASuperSideScroller_Player::Sprint);
	PlayerInputComponent->BindAction("Throw", IE_Pressed, this, &ASuperSideScroller_Player::Throw);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ASuperSideScroller_Player::StopSprinting);
}

void ASuperSideScroller_Player::Sprint()
{
	if (!bIsSprinting)
	{
		UE_LOG(LogMyGame, Verbose, TEXT("Started Sprinting"));
		bIsSprinting = true;
		GetCharacterMovement()->MaxWalkSpeed = 500.0f;
	}
}

void ASuperSideScroller_Player::Throw()
{
	if (ThrowMontage)
	{
		bool bIsMontagePlaying = GetMesh()->GetAnimInstance()->Montage_IsPlaying(ThrowMontage);
		if (!bIsMontagePlaying)
		{
			GetMesh()->GetAnimInstance()->Montage_Play(ThrowMontage, 1.0f);
		}
	}
}

void ASuperSideScroller_Player::StopSprinting()
{
	if (bIsSprinting)
	{
		UE_LOG(LogMyGame, Verbose, TEXT("Finish Sprinting"));
		bIsSprinting = false;
		GetCharacterMovement()->MaxWalkSpeed = 300.0f;
	}
}

void ASuperSideScroller_Player::SpawnProjectile()
{
	if (PlayerProjectile)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParameters;
			SpawnParameters.Owner = this;
			FVector SpawnLocation = this->GetMesh()->GetSocketLocation(FName("ProjectileSocket"));
			FRotator Rotation = GetActorForwardVector().Rotation();
			APlayerProjectile* Projectile = World->SpawnActor<APlayerProjectile>(PlayerProjectile, SpawnLocation,
				Rotation, SpawnParameters);
			if (Projectile)
			{
				Projectile->CollisionComp->MoveIgnoreActors.Add(SpawnParameters.Owner);
			}
		}
	}
}

void ASuperSideScroller_Player::IncrementNumberofCollectables(int32 Value)
{
	if (Value <= 0)
	{
		return;
	}
	else
	{
		NumberOfCollectables += Value;
		UE_LOG(LogTemp, Warning, TEXT("Number of Coins: %d"), NumberOfCollectables);
	}
	
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "SuperSideScroller_Player.h"
#include "SuperSideScroller.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimInstance.h"
#include "PlayerProjectile.h"
#include "Engine/World.h"
#include "Components/SphereComponent.h"
#include "TimerManager.h"

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
		bIsSprinting = true;
		if (bHasPowerupActive)
		{
			GetCharacterMovement()->MaxWalkSpeed = 900.0f;
		}
		else
		{
			GetCharacterMovement()->MaxWalkSpeed = 500.0f;			
		}
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
		bIsSprinting = false;
		if (bHasPowerupActive)
		{
			GetCharacterMovement()->MaxWalkSpeed = 500.0f;
		}
		else
		{
			GetCharacterMovement()->MaxWalkSpeed = 300.0f;
		}		
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

void ASuperSideScroller_Player::IncreaseMovementPowerup()
{
	bHasPowerupActive = true;
	GetCharacterMovement()->MaxWalkSpeed = 500.0f;
	GetCharacterMovement()->JumpZVelocity = 1500.0f;
	UWorld* World = GetWorld();
	if (World)
	{
		World->GetTimerManager().SetTimer(PowerupHandle, this, &ASuperSideScroller_Player::EndPowerup, 8.0f, false);
	}
}

void ASuperSideScroller_Player::EndPowerup()
{
	bHasPowerupActive = false;
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
	GetCharacterMovement()->JumpZVelocity = 1000.0f;
	UWorld* World = GetWorld();
	if (World)
	{
		World->GetTimerManager().ClearTimer(PowerupHandle);
	}
}

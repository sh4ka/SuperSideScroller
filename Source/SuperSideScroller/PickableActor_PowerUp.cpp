// Fill out your copyright notice in the Description page of Project Settings.


#include "PickableActor_PowerUp.h"
#include "SuperSideScroller_Player.h"

void APickableActor_PowerUp::BeginPlay()
{
	Super::BeginPlay();
}

void APickableActor_PowerUp::PlayerPickedUp(ASuperSideScroller_Player* Player)
{
	Player->IncreaseMovementPowerup();
	Super::PlayerPickedUp(Player);
}
